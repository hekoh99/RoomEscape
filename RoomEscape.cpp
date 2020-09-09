#include <bangtal.h>
using namespace bangtal;

int main() {

	auto open1 = false;
	auto is_moved = false;
	
	ScenePtr scene1 = Scene::create("1번 방", "images/배경-1.png");
	ScenePtr scene2 = Scene::create("2번 방", "images/배경-2.png");

	auto key = Object::create("images/열쇠.png", scene1, 600, 150);
	auto door1 = Object::create("images/문-오른쪽-닫힘.png", scene1, 800, 270);

	key->setScale(0.3f);
	key->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool {
		key->pick();
		return true;
		});
	auto vase = Object::create("images/화분.png", scene1, 550, 150);
	vase->setScale(1.2f);
	vase->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool {
		if (action == MouseAction::MOUSE_DRAG_LEFT && is_moved==false) {
			vase->locate(scene1, 450, 150);
			is_moved = true;
		}
		else if(action == MouseAction::MOUSE_DRAG_RIGHT && is_moved == false){
			vase->locate(scene1, 650, 150);
			is_moved = true;
		}
		return true;
	});

	door1->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool {

		if (open1 == true) {
			scene2->enter();
		}
		else if(key->isHanded()){
			door1->setImage("images/문-오른쪽-열림.png");
			open1 = true;
		}
		else {
			showMessage("열쇠가 필요해!");
		}
		return true;
	}); //lambda 함수

	auto door2 = Object::create("images/문-왼쪽-열림.png", scene2, 320, 270);
	auto door3 = Object::create("images/문-오른쪽-닫힘.png", scene2, 910, 270);

	door2->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool {
		scene1->enter();
		return true;
		});

	auto open3 = false;
	auto is_locked = true;
	auto keypad = Object::create("images/키패드.png", scene2, 885, 420);
	keypad->setScale(1.2f);
	auto light = Object::create("images/on스위치.png", scene2, 885, 440);
	light->setScale(0.06f);
	auto is_on = true;

	auto box = Object::create("images/상자.png", scene2, 550, 250);
	box->setScale(0.2f);
	auto hint = Object::create("images/암호.png", scene2, 400, 150, false);

	auto escape = Object::create("images/탈출.png", scene2, 0, 0,false);
	auto end = Object::create("images/끝내기.png", scene2, 510, 200, false);
	end->setScale(0.4f);

	door3->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool {

		if (open3 == true) {
			escape->show();
			end->show();
		}
		else if (is_locked == false && open3 == false) {
			open3 = true;
			door3->setImage("images/문-오른쪽-열림.png");
		}
		else {
			showMessage("문이 잠겨있어..");
		}
		return true;
	});

	door3->setOnKeypadCallback([&](ObjectPtr object)->bool {
		showMessage("철커덕");
		is_locked = false;
		return true;
	});

	
	keypad->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool {

		showKeypad("BANGTAL", door3);

		return true;
	});

	box->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool {

		showMessage("여기엔 아무 것도 없네");
		return true;
	});

	light->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool {

		if (is_on == true) {
			is_on = false;
			light->setImage("images/off스위치.png");
			scene2->setLight(0.3f);
			hint->show();
		}
		else if(is_on == false) {
			is_on = true;
			light->setImage("images/on스위치.png");
			scene2->setLight(1.0f);
			hint->hide();
		}
		return true;
	});

	end->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool {
		endGame();
		return true;
		});

	bangtal::startGame(scene1);

	return 0;
}
