#define _CRT_SECURE_NO_WARNINGS
#include "application.h"
#include "application_delegates.h"
#include "../win32helper/windows_with_macro.h"
#include "../win32gdi/device_context.h"
#include <zlog/zlog.h>
//�߰�
#include <../../resource.h>
#include <random>
#pragma comment(lib, "winmm.lib")

using namespace zee;

#ifdef UNICODE
#define ZEE_WINMAIN_NAME wWinMain
#else
#define ZEE_WINMAIN_NAME WinMain
#endif

class application_win32 : public application {
	friend application& application::get() noexcept;
	friend int
#if defined(_M_CEE_PURE)
		__clrcall
#else
		WINAPI
#endif
		ZEE_WINMAIN_NAME(
			_In_ HINSTANCE hInstance,
			_In_opt_ HINSTANCE hPrevInstance,
			_In_ TCHAR* lpCmdLine,
			_In_ int nShowCmd
		);

	friend LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam);

public:

	using application::app_config_;
	using application::config_;
	using application::is_started_;
	application_win32() {

	}
};

static std::unique_ptr<application_win32> app_inst;

static void create_app_inst() {
	if (!app_inst) {
		app_inst = std::unique_ptr<application_win32>(new application_win32);
	}
}

application& application::get() noexcept {
	create_app_inst();
	return *app_inst;
}


LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

int
#if defined(_M_CEE_PURE)
__clrcall
#else
WINAPI
#endif
ZEE_WINMAIN_NAME(
	_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ TCHAR* lpCmdLine,
	_In_ int nShowCmd
)
{
	create_app_inst();
	const application::config_data& app_config_data = application::get().config();

	app_inst->instance_handle_ = hInstance;
	WNDCLASS WndClass;
	WndClass.cbClsExtra = 0;
	WndClass.cbWndExtra = 0;
	WndClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	WndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	WndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	WndClass.hInstance = hInstance;
	WndClass.lpfnWndProc = (WNDPROC)WndProc;
	WndClass.lpszClassName = app_config_data.app_name.c_str();
	WndClass.lpszMenuName = NULL;
	WndClass.style = CS_HREDRAW | CS_VREDRAW;
	WNDCLASSEX dd;
	RegisterClass(&WndClass);

	app_inst->window_handle_ =
		CreateWindowEx(
			WS_EX_OVERLAPPEDWINDOW,
			app_config_data.app_name.c_str(),
			app_config_data.app_name.c_str(),
			WS_OVERLAPPEDWINDOW,
			0, 0, 0, 0,
			NULL, (HMENU)NULL, app_inst->instance_handle<HINSTANCE>(), NULL
		);

	WINDOWPLACEMENT pl;
	memset(&pl, 0, sizeof(pl));

	shape::recti rc;
	rc.data[1] = app_config_data.window_size;
	rc += app_config_data.window_position;

	pl.length = sizeof(pl);
	pl.showCmd = SW_NORMAL;
	pl.rcNormalPosition.left = rc.get_left  <LONG>();
	pl.rcNormalPosition.top = rc.get_top   <LONG>();
	pl.rcNormalPosition.right = rc.get_right <LONG>();
	pl.rcNormalPosition.bottom = rc.get_bottom<LONG>();

	SetWindowPlacement(app_inst->window_handle<HWND>(), &pl);

	int d = 0;
	MSG Message;
	while (GetMessage(&Message, 0, 0, 0)) {
		TranslateMessage(&Message);
		DispatchMessage(&Message);
	}

	app_inst->app_config_().save();
	app_inst.reset();
	return Message.wParam;
}



//�浹
//cf) contain: ���� ���� ������ ���� ������ ���
//�� vs ��
const shape::collide_type intersect(const math::vec2f& begin, const math::vec2f& end, const math::vec2f& pt) noexcept {	//����ã��.
	if (pt.x >= begin.x && pt.x <= end.x
		&& pt.y >= begin.y && pt.y <= end.y) {
		return shape::collide_type::intersect;
	}
	return shape::collide_type::none;
}
//�� vs �簢��
const shape::collide_type intersect(const shape::rectf& rect, const math::vec2f& pt) noexcept {
	if ((pt.x >= rect.left && pt.x <= rect.right)
		&& (pt.y <= rect.bottom && pt.y >= rect.top)) {
		return shape::collide_type::intersect;
	}
	return shape::collide_type::none;
}
//�� vs ����
const shape::collide_type intersect(const shape::circlef& circle, const math::vec2f& pt) noexcept {
	if (circle.origin.distance_sq(pt) <= circle.radius * circle.radius) {
		return shape::collide_type::intersect;
	}
	return shape::collide_type::none;
}
//�� vs �� 1. ���� ���� �̿� ���
const int comparator(const math::vec2f& l, const math::vec2f& r) {
	//operator< > �Լ� �ʿ�
	int ret;
	if (l.x == r.x) {
		ret = (l.y <= r.y);
	}
	else {
		ret = (l.x <= r.x);
	}
	return ret;
}
void swap(math::vec2f& l, math::vec2f& r) {
	math::vec2f tmp = l;
	l = r;
	r = tmp;
}
const shape::collide_type intersect_with_vector(math::vec2f begin1, math::vec2f end1, math::vec2f begin2, math::vec2f end2) noexcept {
	//���� ��� �ݽð�, ���� ���� �ð�, ���� 0 ����		==> ��ǥ�谡 y������̶� �ݴ��ε�
	//(x1, y1) ���� (x2, y2) == (x1*y2) - (x2*y1).	
	//�� ������ begin���� �ٸ� ������ begin����, end���� ������ �ϳ��� ���, �ϳ��� ������ ���;� ��. �ٸ� ���� begin�� �ݺ�.

	//�� ������ �� ���� ���� �ְų�, ������ ��ġ�� ���
	if (begin1.ccw(begin2) * begin1.ccw(end2) == 0 && begin2.ccw(begin1) * begin2.ccw(end1) == 0) {
		//���� ����. ���� ���ش� ����
		if (comparator(end1, begin1)) {
			swap(begin1, end1);
		}
		if (comparator(end2, begin2)) {
			swap(begin2, end2);
		}
		//����
		if (comparator(begin2, end1) && comparator(begin1, end2)) {
			//���� ����
			if (begin1.x <= begin2.x && begin1.y <= begin2.y && end1.x >= end2.x && end1.y >= end2.y) {	//operator < > �ʿ�
				return shape::collide_type::contain;	//���Եȴٰ� ����
			}
			return shape::collide_type::intersect;
		}
	}
	//�߰����� ��ġ�� ���
	else if (begin1.ccw(begin2) * begin1.ccw(end2) <= 0 && begin2.ccw(begin1) * begin2.ccw(end1) <= 0) {
		return shape::collide_type::intersect;
	}
	return shape::collide_type::none;
}
//�� vs �� 2.1. ������ pt���� ���� 
const shape::collide_type intersect(const math::vec2f& begin1, const math::vec2f& end1, const math::vec2f& begin2, const math::vec2f& end2, math::vec2f& out_pt) noexcept {
	float t;
	float s;
	//������ ������ ���� ���� 1
	float under = (end2.y - begin2.y) * (end1.x - begin1.x) - (end2.x - begin2.x) * (end1.y - begin1.y);
	if (under == 0) {
		//���� ����: �º� ���� �캯 ���� ������ ������ ���
		if (begin1.x <= begin2.x && begin1.y <= begin2.y && end1.x >= end2.x && end1.y >= end2.y) {	//operator < > �ʿ�
			return shape::collide_type::contain;	//���Եȴٰ� ����
		}
		//�Ϻ� ����
		else if (begin1.x <= begin2.x && end1.x >= begin1.x) {
			return shape::collide_type::intersect;
		}
		//����, ������ ����
		else {
			return shape::collide_type::none;
		}
	}
	//������ ������ ���� ���� 2
	float t_ = (end2.x - begin2.x) * (begin1.y - begin2.y) - (end2.y - begin2.y) * (begin1.x - begin2.x);
	float s_ = (end1.x - begin1.x) * (begin1.y - begin2.y) - (end1.y - begin1.y) * (begin1.x - begin2.x);
	t = t_ / under;
	s = s_ / under;
	//���Ŀ��� t�� s�� 0�� 1 ���̿��� ���� �Ǵ�.
	if (t < 0.0 || t > 1.0 || s < 0.0 || s > 1.0) {
		return shape::collide_type::none;
	}
	//����
	out_pt = begin1 + t * (end1 - begin1);
	return shape::collide_type::intersect;
}
//�� vs ��. 2.2. ������ pt���� ���� Ȱ��
const shape::collide_type intersect(const math::vec2f& begin1, const math::vec2f& end1, const math::vec2f& begin2, const math::vec2f& end2) noexcept {
	math::vec2f tmp = { -10000, -10000 };	//�������� �ǹ� ���� �� �� ����
	return intersect(begin1, end1, begin2, end2, tmp);
}

//�� vs �簢�� (�簢���� ���� �����ϴ°�)
const shape::collide_type intersect(const shape::rectf rect, const math::vec2f begin, const math::vec2f end) noexcept {
	math::vec2f lt = { rect.left, rect.top };
	math::vec2f lb = { rect.left, rect.bottom };
	math::vec2f rt = { rect.right, rect.top };
	math::vec2f rb = { rect.right, rect.bottom };

	if (intersect(rect, begin) == shape::collide_type::intersect
		&& intersect(rect, end) == shape::collide_type::intersect) {
		return shape::collide_type::contain;
	}
	else if (intersect(begin, end, lt, lb) == shape::collide_type::intersect
		|| intersect(begin, end, lb, rb) == shape::collide_type::intersect
		|| intersect(begin, end, rb, rt) == shape::collide_type::intersect
		|| intersect(begin, end, rt, lt) == shape::collide_type::intersect) {
		return shape::collide_type::intersect;
	}
	return shape::collide_type::none;
}
//�� vs ���� (������ ���� �����ϴ°�)
const shape::collide_type intersect(const shape::circlef& circle, const math::vec2f& begin, const math::vec2f& end) noexcept {
	//���� �ڵ�� ���۸� �� ���Ǹ� �� ������.
	const math::vec2f& origin_to_begin = begin - circle.origin;
	const math::vec2f& origin_to_end = end - circle.origin;
	float c_begin = origin_to_begin.dot(origin_to_begin) - circle.radius * circle.radius;
	float c_end = origin_to_end.dot(origin_to_end) - circle.radius * circle.radius;

	//������ ���������� ���� �߽ɱ����� �Ÿ��� ���� ���������� ũ�� �ʴٸ�,
	//������ �������� ���� �ȿ� �����Ƿ� ������.
	//������ ��������, ������ �� �ȿ� �ִٸ� ����
	if (c_begin <= 0.0f && c_end <= 0.0f) {
		return shape::collide_type::contain;
	}
	else if (c_begin <= 0.0f || c_end <= 0.0f) {
		return shape::collide_type::intersect;
	}

	const math::vec2f dir = end - begin;
	float length = dir.length();
	if (length == 0.0f) {
		return shape::collide_type::none;
	}
	const math::vec2f normalized_dir = dir / length;
	float b_prime = origin_to_begin.dot(normalized_dir);

	//������ �������� ���� �ۿ� �ְ�, ���� �߽ɿ��� ������ �������� ���ϴ� ���Ϳ� ������ ����
	//���Ͱ� �̷�� ���� 90�� �̸��̶�� �������� ����
	if (b_prime > 0.0f) {
		return shape::collide_type::none;
	}

	//������ b' * b' - a * c�� ����ؾ� ��. �׷��� ������ ���� ���Ͱ� ���� ���͸�,
	//a�� normalized_dir.dot(normalized_dir) = 1
	//�̹Ƿ�, a�� ���� ����.
	float square_root_of_discriminant = sqrt(b_prime * b_prime - c_begin);	//discriminant == �Ǻ���

	float t1 = -b_prime + square_root_of_discriminant;
	if (t1 >= 0.0f && t1 <= length) {
		return shape::collide_type::intersect;
	}
	float t2 = -b_prime + square_root_of_discriminant;
	if (t2 >= 0.0f && t2 <= length) {
		return shape::collide_type::intersect;
	}
	return shape::collide_type::none;
}
const shape::collide_type intersect2(const shape::circlef& circle, const math::vec2f& begin, const math::vec2f& end) noexcept {
	float d_cb = circle.origin.distance(begin);	//���� �������� �� �߽� ���� �Ÿ�
	float d_ce = circle.origin.distance(end);
	//����
	if (d_ce < circle.radius && d_cb < circle.radius) {
		return shape::collide_type::contain;
	}
	//����: ���� �� ���� �� �ȿ�
	else if ((d_cb < circle.radius && d_ce > circle.radius) || (d_cb > circle.radius && d_ce < circle.radius)) {
		return shape::collide_type::intersect;
	}
	else {
		return shape::collide_type::none;
	}
}
//�簢�� vs �簢��
const shape::collide_type intersect(const shape::rectf& rect1, const shape::rectf& rect2) {
	const shape::rectf collision_rect = {
		math::max(rect1.get_left(), rect2.get_left()),
		math::max(rect1.get_top(), rect2.get_top()),
		math::min(rect1.get_right(), rect2.get_right()),
		math::min(rect1.get_bottom(), rect2.get_bottom())
	};
	if (collision_rect.width() != 0 || collision_rect.height() != 0) {	//collision_rect�� �浹�Ǵ� ����
		if (collision_rect == rect1 || collision_rect == rect2) {
			return shape::collide_type::contain;
		}
		//contain �ƴ� �� �������� ����
		else if (!(rect1.get_right() < rect2.get_left()
			|| rect1.get_left() > rect2.get_right()
			|| rect1.get_bottom() < rect2.get_top()
			|| rect1.get_top() > rect2.get_bottom()
			)) {
			return shape::collide_type::intersect;
		}
	}
	return shape::collide_type::none;
}
//���� vs ����
const shape::collide_type intersect(const shape::circlef& circle1, const shape::circlef& circle2) {
	const float rad_minus = math::abs(circle1.radius - circle2.radius);
	const float rad_plus = circle1.radius + circle2.radius;
	const float dist_sq = circle1.origin.distance_sq(circle2.origin);
	//1 �� �� ��, 2 �� �� ����, 3 �� �� ����
	if (dist_sq >= rad_minus * rad_minus && dist_sq <= rad_plus * rad_plus) {
		return shape::collide_type::intersect;
	}
	//4 ������ �ʴ� ���
	if (dist_sq > rad_plus * rad_plus) {
		return shape::collide_type::none;
	}
	//5 ���� ���� ū �� �ȿ� �����鼭 ������ �ʴ� ���, ū ���� �Ű����� �����̸� ����, �ƴϸ� none
	if (dist_sq < rad_minus * rad_minus && circle1.radius > circle2.radius) {
		return shape::collide_type::contain;
	}
	//6 �� ���� �߽��� ���� �������� �ٸ� ���, ū ���� �Ű����� �����̸� ����, �ƴϸ� none
	if (dist_sq == 0 && circle1.radius > circle2.radius) {
		return shape::collide_type::contain;
	}
	return shape::collide_type::none;
}
//�簢�� vs ����
const shape::collide_type intersect(const shape::rectf& rect, const shape::circlef& circle) {
	math::vec2f lt = { rect.left, rect.top };
	math::vec2f lb = { rect.left, rect.bottom };
	math::vec2f rt = { rect.right, rect.top };
	math::vec2f rb = { rect.right, rect.bottom };
	//����: �� �� �� �ϳ��� ��ħ
	if (intersect(circle, lt, lb) == shape::collide_type::intersect
		|| intersect(circle, lb, rb) == shape::collide_type::intersect
		|| intersect(circle, rb, rt) == shape::collide_type::intersect
		|| intersect(circle, rt, lt) == shape::collide_type::intersect) {
		return shape::collide_type::intersect;
	}
	//����
	else if (circle.origin.x > rect.left && circle.origin.x < rect.right
		&& circle.origin.y > rect.top && circle.origin.y < rect.bottom
		&& circle.radius * 2 <= rect.width() && circle.radius * 2 <= rect.height()) {
		return shape::collide_type::contain;
	}
	return shape::collide_type::none;
}
//���� vs �簢��
const shape::collide_type intersect(const shape::circlef& circle, const shape::rectf& rect) {
	math::vec2f lt = { rect.left, rect.top };
	math::vec2f lb = { rect.left, rect.bottom };
	math::vec2f rt = { rect.right, rect.top };
	math::vec2f rb = { rect.right, rect.bottom };
	//����: �� �� �� �ϳ��� ��ħ
	if (intersect(circle, lt, lb) == shape::collide_type::intersect
		|| intersect(circle, lb, rb) == shape::collide_type::intersect
		|| intersect(circle, rb, rt) == shape::collide_type::intersect
		|| intersect(circle, rt, lt) == shape::collide_type::intersect) {
		return shape::collide_type::intersect;
	}
	//���� : �� �� ��� ����
	else if (intersect(circle, lt, lb) == shape::collide_type::contain
		&& intersect(circle, lb, rb) == shape::collide_type::contain
		&& intersect(circle, rb, rt) == shape::collide_type::contain
		&& intersect(circle, rt, lt) == shape::collide_type::contain) {
		return shape::collide_type::contain;
	}
	//�Ʒ� �ڵ嵵 �۵�������, �̹� �ۼ��� �� vs ���� �ڵ� Ȱ��
	/*
	else if (rect.left > circle.origin.x - circle.radius
		&& rect.right < circle.origin.x + circle.radius
		&& rect.bottom < circle.origin.x + circle.radius
		&& rect.top > circle.origin.x - circle.radius) {
		return shape::collide_type::contain;
	}
	*/
	return shape::collide_type::none;
}


//����
static time_t start_time;
static int timer = 0;
static std::string time_str;
static int score = 0;
static std::string score_str;
const static int score_clear = 10;
static bool is_title = true;
static bool is_clear = false;
static math::vec2i mouse_point;
//��ǥ
const enum e_vec {
	lefttop_lt, lefttop_rb,
	righttop_lt, righttop_rb,
	leftmiddle_lt, leftmiddle_rb,
	middlemiddle_lt, middlemiddle_rb,
	rightmiddle_lt, rightmiddle_rb,
	leftbottom_lt, leftbottom_rb,
	rightbottom_lt, rightbottom_rb,
	RectMax,
	title_st, title_st2, title_st3, title_st4, title_st5,
	desc_st, time_st, time_num, score_st, score_num,
	ending_st, ending_st2, ending_st3, ending_st4,
	title_ending_box_lt, title_ending_box_rb,
	Max
};
const static math::vec2i vec_list[Max] = {
	{200, 100}, {300, 200},
	{400, 100}, {500, 200},
	{100, 300}, {200, 400},
	{300, 300}, {400, 400},
	{500, 300}, {600, 400},
	{200, 500}, {300, 600},
	{400, 500}, {500, 600},
	{0, 0},
	{240, 310}, {234, 290}, {234, 330}, {270, 360}, {300, 380},
	{210, 30}, {10, 30}, {55, 30}, {10, 50}, {55, 50},
	{288, 320}, {292, 360}, {370, 360}, {268, 380},
	{220, 250}, {480, 450}
};
//����
static std::random_device rd;	//�õ尪 ��� ����
static std::minstd_rand gen(rd());	//random_device�� ���� ���� ���� ������ �ʱ�ȭ
static std::uniform_int_distribution<int> dis(0, RectMax / 2 - 1);	//0~n �յ��� ������ �����ϱ� ���� �յ� ���� ����

//���� �ʱ�ȭ
void init_game() {
	start_time = 0;
	timer = 0;
	score = 0;
	is_title = true;
	is_clear = false;
	mouse_point = { 0, 0 };
}
//Ÿ��Ʋ
void title_scene(win32gdi::device_context_auto& dc) {
	dc.rectangle({ vec_list[title_ending_box_lt], vec_list[title_ending_box_rb] });
	dc.print_text(vec_list[title_st], TEXT("| ���� �δ��� ��� ������ >_< |"));
	dc.print_text(vec_list[title_st2], TEXT("��-------------------------------------------------��"));
	dc.print_text(vec_list[title_st3], TEXT("��-------------------------------------------------��"));
	dc.print_text(vec_list[title_st4], TEXT("---�ƹ� Ű�� ���� ����---"));
	dc.print_text(vec_list[title_st5], TEXT("���� ��: ������"));
}
//����
void ending_scene(win32gdi::device_context_auto& dc) {
	is_clear = true;
	dc.rectangle({ vec_list[title_ending_box_lt], vec_list[title_ending_box_rb] });
	dc.print_text(vec_list[ending_st], TEXT("�� ���߾��!!!!!!!!!!!"));
	dc.print_text(vec_list[ending_st2], TEXT("�ɸ� �ð�:      ��"));
	dc.print_text(vec_list[ending_st3], to_tstring(time_str));
	dc.print_text(vec_list[ending_st4], TEXT("---�ƹ� Ű�� ���� �����---"));
}
//�ΰ���
void game_scene(win32gdi::device_context_auto& dc, win32gdi::device_context_dynamic& image) {
	dc.print_text(vec_list[desc_st], TEXT("���� ���� �δ��㸦 ��� 10���� ȹ���ϼ���"));
	dc.print_text(vec_list[time_st], TEXT("�ð� : "));
	time_str = to_string(timer);	//int�� to_tstring �ϸ� bool������ ���ͼ� string ��ħ
	dc.print_text(vec_list[time_num], to_tstring(time_str));
	dc.print_text(vec_list[score_st], TEXT("���� : "));
	score_str = to_string(score);
	dc.print_text(vec_list[score_num], to_tstring(score_str));

	image.load_image(TEXT("./resource/dig.bmp"));
	for (int i = 0; i <= 12; i += 2) {
		image.transparent_blt(dc, vec_list[i], RGB(195, 195, 195));
	}
}
//����(�Ѷ���)
enum e_monster_state {
	die,
	alive
};
class monster {
public:
	explicit monster() : hp(alive) {}
	~monster() {}
	void spawn(int& rand_location, const int& other_rand_location, int& spawn_delay);
	void spawn_2nd(bool& is_ani_2nd);
	void attacked(const shape::recti& rand_rect);
	void spawn_ani(const HWND& hWnd, win32gdi::device_context_auto& dc, win32gdi::device_context_dynamic& image,
		const int& rand_location, bool& is_ani_2nd, shape::recti& rand_rect) const;
	void attacked_ani(const HWND& hWnd, win32gdi::device_context_auto& dc, win32gdi::device_context_dynamic& image,
		const int& rand_location) const;
	const int& get_hp() const { return hp; }
private:
	int hp;
};
void monster::spawn(int& rand_location, const int& other_rand_location, int& spawn_delay) {
	rand_location = dis(gen);
	while (rand_location == other_rand_location) {
		rand_location = dis(gen);
	}
	hp = alive;
}
void monster::spawn_2nd(bool& is_ani_2nd) {
	is_ani_2nd = true;
}
void monster::attacked(const shape::recti& rand_rect) {
	if (intersect(rand_rect, mouse_point) != shape::collide_type::none) {
		if (hp == alive) {
			hp = die;
			score++;
			PlaySound(TEXT("./resource/Hit_Hurt14.wav"), nullptr, SND_ASYNC);
		}
	}
}
void monster::spawn_ani(const HWND& hWnd, win32gdi::device_context_auto& dc, win32gdi::device_context_dynamic& image,
	const int& rand_location, bool& is_ani_2nd, shape::recti& rand_rect) const {
	image.load_image(TEXT("./resource/monster_spawn.bmp"));
	image.transparent_blt(dc, vec_list[rand_location * 2], RGB(195, 195, 195));
	/*
	* //Ÿ�̹� ���з� �ּ�
	if (is_ani_2nd) {
		is_ani_2nd = false;
		image.load_image(TEXT("./resource/monster.bmp"));
		image.transparent_blt(dc, vec_list[rand_location * 2], RGB(195, 195, 195));
	}*/
	rand_rect = { vec_list[rand_location * 2], vec_list[rand_location * 2 + 1] }; //��ġ ���� (���콺 ������ ���� �簢�� �浹)
}
void monster::attacked_ani(const HWND& hWnd, win32gdi::device_context_auto& dc, win32gdi::device_context_dynamic& image,
	const static int& rand_location) const {
	image.load_image(TEXT("./resource/monster_die.bmp"));
	image.transparent_blt(dc, vec_list[rand_location * 2], RGB(195, 195, 195));
}
//����
LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam) {
	//https://docs.microsoft.com/en-us/windows/win32/winmsg/window-notifications
	HDC hdc;
	PAINTSTRUCT ps;

	static monster mon1;
	static monster mon2;
	static int spawn_delay_1 = 2;
	static int spawn_delay_2 = 2;
	static bool is_ani_2nd_1 = false;
	static bool is_ani_2nd_2 = false;
	static int rand_location_1;
	static int rand_location_2;
	static shape::recti rand_rect_1;
	static shape::recti rand_rect_2;

	switch (iMessage) {
		//https://docs.microsoft.com/en-us/windows/win32/winmsg/wm-move
	case WM_CREATE:
	{
		app_inst->is_started_ = true;
		application_delegates::on_started().broadcast(application::get());
		win32gdi::device_context_auto temp_dc(hWnd, win32gdi::device_context_auto_type::temp);

		SetTimer(hWnd, 1, 1000, nullptr);	//�������� �ð�
		SetTimer(hWnd, 2, 1000, nullptr);	//����1 ���� �ð�
		SetTimer(hWnd, 3, 1500, nullptr);	//����2 ���� �ð�
		return 0;
	}
	case WM_TIMER:
	{
		win32gdi::device_context_auto temp_dc(hWnd, win32gdi::device_context_auto_type::temp);
		switch (wParam)
		{
		case 1:
			time(&start_time);	//���� �� ���� �ð� ����
			timer++;
			break;
		case 2:
			SetTimer(hWnd, 4, 500, nullptr);	//����1 ���� 2��° �ִ� ����. case 4
			mon1.spawn(rand_location_1, rand_location_2, spawn_delay_1);
			break;
		case 3:
			SetTimer(hWnd, 5, 500, nullptr);	//����2 ���� 2��° �ִ� ����. case 5
			mon2.spawn(rand_location_2, rand_location_1, spawn_delay_2);
			break;
		case 4:
			mon1.spawn_2nd(is_ani_2nd_1);
			break;
		case 5:
			mon2.spawn_2nd(is_ani_2nd_2);
		}

		InvalidateRect(hWnd, nullptr, FALSE);
		return 0;
	}
	case WM_MOVE:
	{
		//auto& position = app_inst->config_().window_position;
		//position.x = (int32)(short)LOWORD(lParam);   // horizontal position 
		//position.y = (int32)(short)HIWORD(lParam);   // vertical position
		return 0;
	}
	case WM_MOUSEMOVE:
	{
		//���콺 �̵�.
		//mouse_position.x = (int32)(short)LOWORD(lParam);
		//mouse_position.y = (int32)(short)HIWORD(lParam);
		//ZEE_LOG(normal, TEXT("app"), TEXT("mouse moved [%s]"), to_tstring(mouse_position).c_str());
		return 0;
	}

	case WM_LBUTTONDOWN: //���콺 Ŭ��
	{
		win32gdi::device_context_auto temp_dc(hWnd, win32gdi::device_context_auto_type::paint);

		mouse_position.x = (int32)(short)LOWORD(lParam);
		mouse_position.y = (int32)(short)HIWORD(lParam);

		mon1.attacked(rand_rect_1);
		mon2.attacked(rand_rect_2);

		InvalidateRect(hWnd, nullptr, FALSE);
		return 0;
	}
	case WM_LBUTTONUP:
	{
		return 0;
	}
	case WM_COMMAND:
	{
		win32gdi::device_context_auto temp_dc(hWnd, win32gdi::device_context_auto_type::paint);

		switch (LOWORD(wParam)) {
		case 1:
			break;
		}
	}
	case WM_SIZE:
	{
		auto& app = application::get();
		int d = 0;
		return 0;
	}
	case WM_CHAR:
	{
		InvalidateRect(hWnd, NULL, FALSE);
		return 0;
	}
	case WM_KEYDOWN:
	{
		if (is_title) {
			is_title = false;
			InvalidateRect(hWnd, nullptr, FALSE);
		}
		if (is_clear) {
			is_clear = false;
			is_title = true;
			InvalidateRect(hWnd, nullptr, FALSE);
		}
	}
	case WM_PAINT:
	{
		win32gdi::device_context_auto temp_dc(hWnd, win32gdi::device_context_auto_type::paint);
		win32gdi::device_context_dynamic temp_image;

		temp_image.load_image(TEXT("./resource/back.bmp"));
		temp_image.bit_blt(temp_dc, {});

		if (is_title) {
			init_game();
			title_scene(temp_dc);
			return 0;
		}
		if (score >= score_clear) {
			ending_scene(temp_dc);
			return 0;
		}
		game_scene(temp_dc, temp_image);

		if (mon1.get_hp() == alive) {
			mon1.spawn_ani(hWnd, temp_dc, temp_image, rand_location_1, is_ani_2nd_1, rand_rect_1);
		}
		if (mon1.get_hp() == die) {
			mon1.attacked_ani(hWnd, temp_dc, temp_image, rand_location_1);
		}
		if (mon2.get_hp() == alive) {
			mon2.spawn_ani(hWnd, temp_dc, temp_image, rand_location_2, is_ani_2nd_2, rand_rect_2);
		}
		if (mon2.get_hp() == die) {
			mon2.attacked_ani(hWnd, temp_dc, temp_image, rand_location_2);
		}

		/*
		//�������� �Լ����� �� �����س��µ� temp_dc.
		//ZEE_LOG(normal, TEXT("paint"), TEXT("log test. %s %d"), TEXT("test"), 10);

		//�̷� DeviceContext����� �ű⼭�� gdi (�׷��� ����̽� �������̽�)�� �����ִ� �ڵ��ε�
		//�����ϰ� ���ؼ� �׸��׸��� �����ִ� ��ü��.
		//������ �ؼ� �̷��� ������ �� �����ߵǰ� �ϴ� �׷� �κ��� ������.
		//����
		//cc.origin = mouse_position; //+application::get().app_config().data().window_size / 2;
		//temp_dc.ellipse(300, 300, 600, 900);//Ÿ��

		//�����
		win32gdi::device_context_auto temp_dc(hWnd, win32gdi::device_context_auto_type::paint);

		shape::rectf rc1(100, 100, 200, 200);
		shape::rectf rc2(200, 200, 250, 250);
		//rc1.data[1] = mouse_position;
		temp_dc.rectangle(rc1);
		temp_dc.rectangle(rc2);

		shape::circlef cc1;
		shape::circlef cc2;
		cc1.origin = mouse_position;
		//cc1.origin = { 500, 500 };
		cc1.radius = 200;
		cc2.origin = { 500, 500 };
		cc2.radius = 50;
		temp_dc.circle(cc1);
		temp_dc.circle(cc2);

		//�浹 �׽�Ʈ
		//�簢�� vs �簢��
		if (intersect(rc1, rc2) == shape::collide_type::intersect) {
			ZEE_LOG(normal, TEXT("paint"), TEXT("1-- rc1 inter rc2"));
		}
		if (intersect(rc1, rc2) == shape::collide_type::contain) {
			ZEE_LOG(normal, TEXT("paint"), TEXT("2-- rc1 con rc2"));
		}
		//���� vs ����
		if (intersect(cc1, cc2) == shape::collide_type::intersect) {
			ZEE_LOG(normal, TEXT("paint"), TEXT("3-- cc1 inter cc2"));
		}
		if (intersect(cc1, cc2) == shape::collide_type::contain) {
			ZEE_LOG(normal, TEXT("paint"), TEXT("4-- cc1 con cc2"));
		}
		//�簢�� vs ����
		if (intersect(rc1, cc1) == shape::collide_type::intersect) {
			ZEE_LOG(normal, TEXT("paint"), TEXT("5-- rc1 inter cc1"));
		}
		if (intersect(rc1, cc1) == shape::collide_type::contain) {
			ZEE_LOG(normal, TEXT("paint"), TEXT("6-- rc1 con cc1"));
		}
		//���� vs �簢��
		if (intersect(cc1, rc1) == shape::collide_type::intersect) {
			ZEE_LOG(normal, TEXT("paint"), TEXT("7-- cc1 inter rc1"));
		}
		if (intersect(cc1, rc1) == shape::collide_type::contain) {
			ZEE_LOG(normal, TEXT("paint"), TEXT("8-- cc1 con rc1"));
		}
		*/
		return 0;
	}
	case WM_DESTROY:
		KillTimer(hWnd, 1);
		KillTimer(hWnd, 2);
		KillTimer(hWnd, 3);
		KillTimer(hWnd, 4);
		KillTimer(hWnd, 5);
		PostQuitMessage(0);
		return 0;
	}
	return(DefWindowProc(hWnd, iMessage, wParam, lParam));
}


