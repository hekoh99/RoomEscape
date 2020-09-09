#include <bangtal.h>
using namespace bangtal;

int main() {

	auto open1 = false;
	auto is_moved = false;
	
	ScenePtr scene1 = Scene::create("1번 방", "images/배경-1.png");
	ScenePtr scene2 = Scene::create("2번 방", "images/배경-2.png");
	ScenePtr scene3 = Scene::create("3번 방", "images/배경-3.png");

	auto key = Object::create("images/열쇠.png", scene1, 600, 150);
	auto door1 = Object::create("images/문-오른쪽-닫힘.png", scene1, 800, 270);
	auto orange = Object::create("images/주황이.png", scene1, 900, 100);
	auto star1 = Object::create("images/별.png", scene1, 900, 100, false);
	auto star2 = Object::create("images/별.png", scene2, 900, 100);
	auto star3 = Object::create("images/별.png", scene3, 900, 100);
	star1->setScale(0.5f);
	star2->setScale(0.5f);
	star3->setScale(0.5f);
	star1->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool {
		star1->pick();
		return true;
		});
	star2->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool {
		star2->pick();
		return true;
		});
	star3->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool {
		star3->pick();
		return true;
		});

	key->setScale(0.3f);
	key->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool {
		key->pick();
		return true;
		});
	auto vase = Object::create("images/화분.png", scene1, 550, 150);
	vase->setScale(1.2f);

	auto apple = Object::create("images/사과.png", scene1, 550, 180);
	apple->setScale(0.4f);

	apple->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool {
		apple->pick();
		return true;
		});
	bool ate = false;
	orange->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool {

		if (apple->isHanded()) {
			apple->drop();
			apple->hide();
			orange->setImage("images/웃는-주황이.png");
			star1->show();
			ate = true;
		}
		else if(ate == false){
			showMessage("배고파!!");
		}
		return true;
		});

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
			key->drop();
			key->hide();
			open1 = true;
		}
		else {
			showMessage("열쇠가 필요해!");
		}
		return true;
	}); //lambda 함수

	auto door2 = Object::create("images/문-왼쪽-열림.png", scene2, 320, 270);
	auto door3 = Object::create("images/문-오른쪽-닫힘.png", scene2, 910, 270);
	auto door4 = Object::create("images/문-왼쪽-열림.png", scene3, 290, 290);

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

	door3->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool {

		if (open3 == true) {
			scene3->enter();
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

		showKeypad("AAAAAB", door3);

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


	door4->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool {
		scene2->enter();
		return true;
		});

	auto area1 = Object::create("images/투명위치.png", scene3, 680, 400);
	area1->setScale(0.5f);
	auto area2 = Object::create("images/투명위치.png", scene3, 860, 620);
	area2->setScale(0.5f);
	auto area3 = Object::create("images/투명위치.png", scene3, 1030, 340);
	area3->setScale(0.5f);

	bool fill1 = false;
	bool fill2 = false;
	bool fill3 = false;

	int collect = 0;
	auto hole = Object::create("images/구멍.png", scene3, 450, 100, false);
	area1->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool {
		if (fill1==false && star1->isHanded()) {
			fill1 = true;
			star1->drop();
			star1->setScale(0.8f);
			star1->locate(scene3, 650, 370);
			collect++;
			if (collect == 3) {
				hole->show();
			}
		}
		else if (fill1 == false && star2->isHanded()) {
			fill1 = true;
			star2->drop();
			star2->setScale(0.8f);
			star2->locate(scene3, 650, 370);
			collect++;
			if (collect == 3) {
				hole->show();
			}
		}
		else if (fill1 == false && star3->isHanded()) {
			fill1 = true;
			star3->drop();
			star3->setScale(0.8f);
			star3->locate(scene3, 650, 370);
			collect++;
			if (collect == 3) {
				hole->show();
			}
		}
		return true;
		});

	area2->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool {
		if (fill2 == false && star1->isHanded()) {
			fill2 = true;
			star1->drop();
			star1->setScale(0.8f);
			star1->locate(scene3, 830, 590);
			collect++;
			if (collect == 3) {
				hole->show();
			}
		}
		else if (fill2 == false && star2->isHanded()) {
			fill2 = true;
			star2->drop();
			star2->setScale(0.8f);
			star2->locate(scene3, 830, 590);
			collect++;
			if (collect == 3) {
				hole->show();
			}
		}
		else if (fill2 == false && star3->isHanded()) {
			fill2 = true;
			star3->drop();
			star3->setScale(0.8f);
			star3->locate(scene3, 830, 590);
			collect++;
			if (collect == 3) {
				hole->show();
			}
		}
		return true;
		});

	area3->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool {
		if (fill3 == false && star1->isHanded()) {
			fill3 = true;
			star1->drop();
			star1->setScale(0.8f);
			star1->locate(scene3, 1000, 310);
			collect++;
			if (collect == 3) {
				hole->show();
			}
		}
		else if (fill3 == false && star2->isHanded()) {
			fill3 = true;
			star2->drop();
			star2->setScale(0.8f);
			star2->locate(scene3, 1000, 310);
			collect++;
			if (collect == 3) {
				hole->show();
			}
		}
		else if (fill3 == false && star3->isHanded()) {
			fill3 = true;
			star3->drop();
			star3->setScale(0.8f);
			star3->locate(scene3, 1000, 310);
			collect++;
			if (collect == 3) {
				hole->show();
			}
		}
		return true;
		});

	auto escape = Object::create("images/탈출.png", scene3, 0, 0, false);
	auto end = Object::create("images/끝내기.png", scene3, 510, 200, false);
	end->setScale(0.4f);
	end->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool {
		endGame();
		return true;
		});

	hole->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool {
		escape->show();
		end->show();
		star1->hide();
		star2->hide();
		star3->hide();
		return true;
		});

	bangtal::startGame(scene1);

	return 0;
}
