#include <iostream>
#include <SFML\Audio.hpp>
#include <SFML\Window.hpp>
#include <SFML/Graphics.hpp>
#include <time.h>
#include<vector>
#include <fstream>
using namespace std;
using namespace sf;


//----------------------------------------//
//GLOBAL VARIABLES
Vector2f bullet1_position = { 0,0 };
Vector2f bullet2_position = { 0,0 };
Vector2f gunvelocity = { 1.3, 1.3 };
Vector2f bulletvelocity = { 0, -1.5 };
Vector2f exp_position_r_l = { 0,0 };
Vector2f exp_position = { 0,0 };
Vector2f rockpos = { 0,0 };
Event event;
float dt = 0;
int levels = -1;
int healthship = 10;
int healthship2 = 10;
bool paused = false;
int volumee = 90;
string namee = "player";

//----------------------------------------//






//STRUCTS
//----------------------------------------//
struct playerhistory {
	long long score = 0;
	string name1;
};
vector<playerhistory>history;

struct chicken {
	Sprite arrchicken[100]; //array ll chicken 
	bool ch_intersect = false;
	bool ch_intersect2 = false;
	float xstep[100];//bta3t harket el chicken
	int killed[100] = {};
	int spawn[100] = {};//3lshan el chicken t3raf te7ara 
	int health[100];
	int x = 270; //first position ll chicken in x;
	int y = 75; //first position ll chicken in y
	int counter = 0;
	int ch_exptimer = 0;
	int ch_exptimer2 = 0;
	int ch_index = 0;
	int ch_index2 = 0;
	int hitwall = 0;
	float timerr[100] = {}; //for red ch
	float delayr = 0.12; // for red ch
	float timerg = 0; // for green ch
	float delayg = 0.07; //for green ch
}ch;
struct egg {
	bool egg_intersect = false;
	int egg_exptimer = 0;
	int egg_index = 0;
	bool egg_intersect2 = false;
	int egg_exptimer2 = 0;
	int egg_index2 = 0;
}egg;
struct bullets
{

	int shoottimer = 0; //el wa2t been el tal2
	int bulletcount[55] = { 0 };
	vector<Sprite>bulletsv;
	//for the first boss
	bool gun_shoot = false;
	bool shoot = false;
	bool bulletboss = 0;
	int bulletind = 0;
	int BulletCounter = 0;
	int ExplosionTimer = 0;
	//for the blue & purple bosses
	bool bullet_purpleboss = 0; //for first boss in second boss level 
	bool bullet_blueboss = 0; //for second boss in second boss level
	int BulletCounter_purpleBoss = 0; //for first boss in second boss level
	int BulletCounter_blueboss = 0;//for second boss in second boss level
	int ExplosionTimer_purpleboss = 0; //for first boss in second boss level
	int ExplosionTimer_blueboss = 0;//for second boss in second boss level

	bool gun_shoot2 = false;
	bool shoot2 = false;
	int bulletind2 = 0;
	int shoottimer2 = 0; //el wa2t been el tal2
	int bulletcount2[55] = { 0 };
	vector<Sprite>bulletsv2;
}b;
struct intersect_explosion
{
	//gun with bosses 
	bool gunintersect_with_purple = false;
	int gun_exptimer_with_purple = 0;
	bool gunintersect_with_blue = false;
	int gun_exptimer_with_blue = 0;
	bool gunintersect_with_purple2 = false;
	int gun_exptimer_with_purple2 = 0;
	bool gunintersect_with_blue2 = false;
	int gun_exptimer_with_blue2 = 0;
}e;
struct eggs {
	bool eggintersect_purple = false;
	int eggexptimer_purple = 0;
	Vector2f eggexpposition_purple = { 0,0 };
	bool eggintersect_blue = false;
	int eggexptimer_blue = 0;
	Vector2f eggexpposition_blue = { 0,0 };
	Sprite egg_frompurple;
	Sprite egg_fromblue;
	bool eggintersect = false;
	int eggexptimer = 0;
	Vector2f eggexpposition = { 0,0 };
	Sprite egg;
}oneegg[3];
struct rock
{
	bool bullet_with_rock = false;
	int rockrandom = 0;
	int rockind = 0;
	int exptimer = 0;
	int rocks_counter = 0;
	int co = 0;
}r;
struct gifts
{
	bool gained_red_gift = false;
	bool gained_green_gift = false;
	bool gained_red_gift2 = false;
	bool gained_green_gift2 = false;
}g;
struct chickenBoss {
	Sprite chickenboss;
	Vector2f velocity = { 0.5,0.2 };
	Vector2f boss_exp_pos = { 0,0 };
	float bosstimer = 0;
	bool intersect = false;
	int h = 0;
	int bossexptimer = 0;
	int exptimer = 0;
	bool bosskilled = false;
	bool intersect2 = false;
	int bossexptimer2 = 0;
	int exptimer2 = 0;
}boss;
struct bosspurple {
	Sprite purpleboss;
	int f = 0;
	float purplebosstimer = 0;
	Vector2f purple_boss_velocity = { 0.5,0.2 };
	bool killedpurple = false;
}purple;
struct bossblue {
	Sprite blueboss;
	int j = 0;
	float bluebosstimer = 0;
	Vector2f blue_boss_velocity = { -0.5,0.2 };
	bool killedblue = false;
}blue;
//----------------------------------------//






//FUNCTIONS
//------------------------------------------------------------------------------------------------------------------------------------------------------------//
//SHOOTING
void setup_red_chicken(Sprite chicken) {
	//first line 
	for (int j = 0; j < 10; j++) {
		ch.arrchicken[j] = chicken;
		ch.arrchicken[j].setPosition(ch.x, ch.y);
		ch.x += 150;
	}
	ch.x = 270;

	//second line
	for (int j = 10; j < 20; j++) {
		ch.arrchicken[j] = chicken;
		ch.arrchicken[j].setPosition(ch.x, 180);
		ch.x += 150;
	}
	ch.x = 270;

	//third line
	for (int j = 20; j < 30; j++) {
		ch.arrchicken[j] = chicken;
		ch.arrchicken[j].setPosition(ch.x, 285);
		ch.x += 150;
	}

}
void setup_green_chicken(Sprite chickeng) {
	ch.x = -400;
	for (int j = 30; j < 40; j++) {
		ch.arrchicken[j] = chickeng;
		ch.arrchicken[j].setPosition(ch.x, 100);
		ch.arrchicken->move(ch.xstep[j], 0);
		ch.x -= 150;
	}
	ch.x = -400;
	//second line
	for (int j = 40; j < 50; j++) {
		ch.arrchicken[j] = chickeng;
		ch.arrchicken[j].setPosition(ch.x, 220);
		ch.arrchicken->move(ch.xstep[j], 0);
		ch.x -= 150;
	}
	ch.x = -400;
	//third line
	for (int j = 50; j < 60; j++) {
		ch.arrchicken[j] = chickeng;
		ch.arrchicken[j].setPosition(ch.x, 340);
		ch.arrchicken->move(ch.xstep[j], 0);
		ch.x -= 150;
	}
}
void set_damage(Sprite arrdamage[], Clock damageclock[], int start, int end) {
	//for loop bt3mel check en el chicken mattet w btrsem el damage
	for (int f = start; f <= end; f++) {
		if (ch.killed[f] == 1) //bool bymshy 3la kol far5a yshof mattet wla laa
		{
			arrdamage[f].setPosition(ch.arrchicken[f].getPosition().x, ch.arrchicken[f].getPosition().y);
			if (damageclock[f].getElapsedTime().asSeconds() > 0.2) {
				arrdamage[f].setScale(0, 0);//lma y3dy 0.2 s elrasma hat5tfy
				damageclock[f].restart();
			}
		}
		else
			damageclock[f].restart();
	}
}


//SHOOTING 
void one_bullet(Sprite gun, Sprite& fire)
{
	fire.setPosition(gun.getPosition().x - bullet1_position.x, gun.getPosition().y - bullet1_position.y);
	fire.setScale(1, 1);
	b.bulletsv.push_back(fire);
}
void shooting_one_bullet(Sprite& fire, Sprite& gun, Sprite& gun_r_l, Sound& shot)
{
	if (b.shoottimer < 150) {// el far2 ben el tal2a w el b3dha
		b.shoottimer++;
	}
	if (Keyboard::isKeyPressed(Keyboard::Space) && (b.shoottimer >= 150)) {
		b.shoottimer = 0; //bnsfr el counter tany 34an ntl3 tal2 gded
		b.shoot = true;
		shot.play();

		//3shan azbot position el bullet w el gun mayel ymen
		if (Keyboard::isKeyPressed(Keyboard::Right)) {
			bullet1_position = { 8,110 };
			one_bullet(gun_r_l, fire);
		}
		//3shan azbot position el bullet w el gun mayel shmal
		else if (Keyboard::isKeyPressed(Keyboard::Left)) {
			bullet1_position = { -8,110 };
			one_bullet(gun_r_l, fire);
		}
		// da f 7alt el gun el 3ady 
		else {
			bullet1_position = { 7,110 };
			one_bullet(gun, fire);
		}
	}
	if (b.shoot) {
		for (int i = 0; i < b.bulletsv.size(); i++)
			b.bulletsv[i].move(bulletvelocity);
	}
}
void two_bullets(Sprite arrfire[], Sprite gun)
{
	arrfire[0].setPosition(gun.getPosition().x + bullet1_position.x, gun.getPosition().y - bullet1_position.y);
	arrfire[1].setPosition(gun.getPosition().x - bullet2_position.x, gun.getPosition().y - bullet2_position.y);
	arrfire[0].setScale(1, 1);
	arrfire[1].setScale(1, 1);
	b.bulletsv.push_back(arrfire[0]);
	b.bulletsv.push_back(arrfire[1]);

	for (int i = 0; i < b.bulletsv.size(); i++) {
		if (b.bulletsv[i].getPosition().y <= 50) {
			b.bulletsv.erase(b.bulletsv.begin() + i);
		}
	}
}
void shooting_two_bullets(Sprite arrfire[], Sprite gun, Sprite gun_r_l, Sound& shot)
{
	if (b.shoottimer < 150) {// el far2 ben el tal2a w el b3dha
		b.shoottimer++;
	}

	if (Keyboard::isKeyPressed(Keyboard::Space) && (b.shoottimer >= 150)) {
		b.shoottimer = 0; //bnsfr el counter tany 34an ntl3 tal2 gded
		b.shoot = true;
		shot.play();
		//3shan azbot position el bullet w el gun mayel ymen
		if (Keyboard::isKeyPressed(Keyboard::Right)) {
			bullet1_position = { 20,110 };
			bullet2_position = { 25,110 };
			two_bullets(arrfire, gun_r_l);
		}
		//3shan azbot position el bullet w el gun mayel shmal
		else if (Keyboard::isKeyPressed(Keyboard::Left)) {
			bullet1_position = { 20,110 };
			bullet2_position = { 25,110 };
			two_bullets(arrfire, gun_r_l);
		}
		// da f 7alt el gun el 3ady 
		else {
			bullet1_position = { 20,110 };
			bullet2_position = { 35,110 };
			two_bullets(arrfire, gun);

		}
	}
	if (b.shoot) {
		for (int i = 0; i < b.bulletsv.size(); i++) {
			b.bulletsv[i].move(bulletvelocity);
		}
	}
}
void gun_death_nobullet(vector<Sprite>& bulletsv) {
	for (int i = 0; i < b.bulletsv.size(); i++) {
		bulletsv[i].setScale(0, 0);
		bulletsv[i].move(0, 0);
	}
}
//BACKGROUND
void movingbackground(float scrollspeed, Sprite& movingspace1, Sprite& movingspace2) {
	//  speed beta3 el background

	float scrollSpeed = 0.1;
	//DRAWING OBJECTS
			// Scroll background down
	movingspace1.move(0, scrollSpeed);
	movingspace2.move(0, scrollSpeed);

	// Check if a sprite has left the bottom of the screen
	if (movingspace1.getPosition().y > 1090)
	{
		// Move it to the top of the other sprite
		movingspace1.setPosition(0, movingspace2.getPosition().y - movingspace1.getGlobalBounds().height);
	}
	else if (movingspace2.getPosition().y > 1090)
	{
		// Move it to the top of the other sprite
		movingspace2.setPosition(0, movingspace1.getPosition().y - movingspace2.getGlobalBounds().height);
	}


}

//COLLISIONS
void shooting_gain_gifts(Sprite gun, Sprite& gift, Sprite& giftgreen, Sprite gun_r_l, Sprite arrfire[], Sprite fire, Sprite firegreen, Sound& shot, Sound& giftt) {
	if (gun.getGlobalBounds().intersects(gift.getGlobalBounds()) || gun_r_l.getGlobalBounds().intersects(gift.getGlobalBounds())) {
		giftt.play();
		gift.setScale(0, 0);
		g.gained_red_gift = true;
		g.gained_green_gift = false;

	}
	else if (gun.getGlobalBounds().intersects(giftgreen.getGlobalBounds()) || gun_r_l.getGlobalBounds().intersects(giftgreen.getGlobalBounds())) {
		giftt.play();
		giftgreen.setScale(0, 0);
		g.gained_green_gift = true;
		g.gained_red_gift = false;
	}
	if (g.gained_red_gift) {
		shot.play();
		shooting_two_bullets(arrfire, gun, gun_r_l, shot);
	}
	else if (g.gained_green_gift) {
		shot.play();
		shooting_one_bullet(firegreen, gun, gun_r_l, shot);
	}
	else {
		shooting_one_bullet(fire, gun, gun_r_l, shot);
		shot.play();

	}

	for (int i = 0; i < b.bulletsv.size(); i++) {
		if (b.bulletsv[i].getPosition().y <= 50) {
			b.bulletsv.erase(b.bulletsv.begin() + i);
		}
	}
}
//gun collisions
void gun_with_eggs_rocks(Sprite& gun, Sprite& gun_r_l, Sprite arregg[], Sprite& explosion1, int start, int end, Sound& exp)
{
	for (int i = start; i < end; i++) {
		if (gun_r_l.getGlobalBounds().intersects(arregg[i].getGlobalBounds())) {
			egg.egg_intersect = true;
			egg.egg_index = i;
			exp_position = { gun_r_l.getPosition().x,gun_r_l.getPosition().y };
		}
	}
	if (egg.egg_intersect)
	{
		egg.egg_exptimer++;
		gun_r_l.setScale(0, 0);
		gun.setScale(0, 0);
		arregg[egg.egg_index].setScale(0, 0);
		explosion1.setPosition(exp_position);
		explosion1.setScale(1, 1);
		if (egg.egg_exptimer > 500) {
			exp.play();
			healthship--;
			explosion1.setScale(0, 0);
			gun_r_l.setScale(1, 1);
			gun_r_l.setPosition(900, 900);
			gun.setPosition(900, 900);
			egg.egg_intersect = false;
			egg.egg_exptimer = 0;
			g.gained_red_gift = false;
			g.gained_green_gift = false;
		}
	}
}
void gun_with_chickens(Sprite& gun, Sprite& gun_r_l, Sprite& explosion1, int start, int end, Sound& exp, long long& totalscore)
{
	for (int i = start; i < end; i++) {
		if (gun_r_l.getGlobalBounds().intersects(ch.arrchicken[i].getGlobalBounds())) {
			ch.ch_intersect = true;
			ch.ch_index = i;
			exp_position = { gun_r_l.getPosition().x,gun_r_l.getPosition().y };
		}
	}
	if (ch.ch_intersect)
	{
		ch.ch_exptimer++;
		gun_r_l.setScale(0, 0);
		gun.setScale(0, 0);
		ch.arrchicken[ch.ch_index].setScale(0, 0);
		explosion1.setPosition(exp_position);
		explosion1.setScale(1, 1);
		if (ch.ch_exptimer > 500) {
			exp.play();
			totalscore += 100;
			ch.counter++;
			healthship--;
			explosion1.setScale(0, 0);
			gun_r_l.setScale(1, 1);
			gun_r_l.setPosition(900, 900);
			gun.setPosition(900, 900);
			ch.ch_intersect = false;
			ch.ch_exptimer = 0;
			g.gained_red_gift = false;
			g.gained_green_gift = false;
		}
	}
}
void get_chicken_leg(Sprite gun, Sprite gun_r_l, Sprite arrleg[], int& score, int& start, int& end, long long& totalscore, int& rocket, Sound& Eating_leg) {
	for (int j = start; j <= end; j++) {
		if (arrleg[j].getGlobalBounds().intersects(gun.getGlobalBounds()) || arrleg[j].getGlobalBounds().intersects(gun_r_l.getGlobalBounds())) {
			Eating_leg.play();
			arrleg[j].setScale(0, 0);
			score += 5;
			totalscore += 50;
		}
	}

	if (score == 50) {
		rocket++;
		score = 0;
	}
}
//sprites collision
void killing_red_chicken(Sprite arrleg[], long long& totalscore, vector<Sprite>& bulletsv, Sound& ch_damdge) {
	for (int j = 0; j < 30; j++) {
		for (int i = 0; i < bulletsv.size(); i++) {
			if (ch.arrchicken[j].getGlobalBounds().intersects(bulletsv[i].getGlobalBounds()))
			{
				ch_damdge.play();
				//el far5a hatmot w hatnzel el dabos
				arrleg[j].setPosition(ch.arrchicken[j].getPosition().x, ch.arrchicken[j].getPosition().y);
				arrleg[j].move(0, 0.4);
				ch.counter++;
				totalscore += 100;
				ch.arrchicken[j].setScale(0, 0);
				bulletsv[i].setScale(0, 0); //lma el fire t5bt elfarha elfire y5tfy
				ch.killed[j] = 1;//3lshan el damage
			}
		}
	}
}
void killing_green_chicken(Sprite arrleg[], long long& totalscore, vector<Sprite>& bulletsv, Sound& ch_damdge)
{

	if (g.gained_red_gift == false) {
		for (int j = 30; j < 60; j++) {
			for (int i = 0; i < bulletsv.size(); i++) {
				if (ch.arrchicken[j].getGlobalBounds().intersects(bulletsv[i].getGlobalBounds()))
				{
					ch_damdge.play();
					bulletsv[i].setScale(0, 0); //lma el fire t5bt elfarha elfire y5tfy
					ch.health[j]--;
					if (ch.health[j] == 0) {
						arrleg[j].setPosition(ch.arrchicken[j].getPosition().x, ch.arrchicken[j].getPosition().y);
						ch.arrchicken[j].setScale(0, 0);
						ch.counter++;
						ch.killed[j] = 1;
						totalscore += 100;
					}
				}
			}
		}
	}

	if (g.gained_red_gift == true || g.gained_green_gift == true) {
		for (int j = 30; j < 60; j++) {
			for (int i = 0; i < bulletsv.size(); i++) {
				if (ch.arrchicken[j].getGlobalBounds().intersects(bulletsv[i].getGlobalBounds()))
				{
					ch_damdge.play();
					bulletsv[i].setScale(0, 0); //lma el fire t5bt elfarha elfire y5tfy
					arrleg[j].setPosition(ch.arrchicken[j].getPosition().x, ch.arrchicken[j].getPosition().y);
					ch.arrchicken[j].setScale(0, 0);
					ch.counter++;
					ch.killed[j] = 1;
					totalscore += 100;
				}
			}
		}
	}
}
void smash_rocks(Sprite arrrocks1[], Sprite& explosion1, Sprite fire, vector<Sprite>& bulletsv, long long& totalscore, Sound& rockexp)
{
	for (int j = 0; j < bulletsv.size(); j++) {
		for (int i = 0; i < 50; i++) {
			if (bulletsv[j].getGlobalBounds().intersects(arrrocks1[i].getGlobalBounds())) {
				rockexp.play();
				r.rockind = i;
				b.bulletind = j;
				r.bullet_with_rock = true;
				rockpos = { arrrocks1[r.rockind].getPosition().x, arrrocks1[r.rockind].getPosition().y };
				bulletsv[b.bulletind].setScale(0, 0);
				b.bulletcount[i]++;
			}
		}
	}
	for (int i = 0; i < 50; i++) {
		if (r.bullet_with_rock && b.bulletcount[i] >= 4) {
			r.exptimer++;
			arrrocks1[r.rockind].setScale(0, 0);
			explosion1.setPosition(rockpos);
			explosion1.setScale(1, 1);
			if (r.exptimer > 400) {
				r.rocks_counter++;
				totalscore += 150;
				explosion1.setScale(0, 0);
				r.bullet_with_rock = false;
				r.exptimer = 0;
				b.bulletcount[i] = 0;
			}
		}
	}
}
//ground
void leg_with_ground(Sprite arrleg[], RectangleShape& ground, Clock legclock[], int start, int end)
{
	for (int j = start; j < end; j++) {
		if (arrleg[j].getGlobalBounds().intersects(ground.getGlobalBounds())) {
			arrleg[j].move(0, 0);
			if (legclock[j].getElapsedTime().asSeconds() > 2) {
				arrleg[j].setScale(0, 0);
				legclock[j].restart();
			}
		}
		else {
			arrleg[j].move(0, 0.7);
			legclock[j].restart();
		}
	}
}
void egg_with_ground(Sprite arregg[], RectangleShape& ground, Sprite arrcrashed_egg[], Clock& crashedclock, int s, int e, Sound& cracked_egg)
{
	for (int i = s; i < e; i++) {
		if (arregg[i].getGlobalBounds().intersects(ground.getGlobalBounds())) {
			cracked_egg.play();
			arrcrashed_egg[i].setPosition(arregg[i].getPosition().x, 950);
			arregg[i].setPosition(0, 100000);
			arrcrashed_egg[i].setScale(1, 1);
		}

		if (oneegg[0].egg.getGlobalBounds().intersects(ground.getGlobalBounds())) {
			cracked_egg.play();
			arrcrashed_egg[0].setPosition(oneegg[0].egg.getPosition().x, 950);
			oneegg[0].egg.setPosition(0, 100000);
			arrcrashed_egg[0].setScale(1, 1);
		}

		if (oneegg[1].egg_fromblue.getGlobalBounds().intersects(ground.getGlobalBounds())) {
			cracked_egg.play();
			arrcrashed_egg[2].setPosition(oneegg[1].egg_fromblue.getPosition().x, 950);
			oneegg[1].egg_fromblue.setPosition(0, 100000);
			arrcrashed_egg[2].setScale(1, 1);
		}

		if (oneegg[1].egg_frompurple.getGlobalBounds().intersects(ground.getGlobalBounds())) {
			cracked_egg.play();
			arrcrashed_egg[2].setPosition(oneegg[1].egg_frompurple.getPosition().x, 950);
			oneegg[1].egg_frompurple.setPosition(0, 100000);
			arrcrashed_egg[2].setScale(1, 1);
		}

	}
	if (crashedclock.getElapsedTime().asSeconds() > 3) {
		for (int i = s; i < e; i++) {
			arrcrashed_egg[i].setScale(0, 0);
		}
		crashedclock.restart();
	}
}


//MOVEMENT
void moving_right(Sprite& gun, Sprite& gun_r_l)
{
	if (Keyboard::isKeyPressed(Keyboard::Right) && gun_r_l.getPosition().x < 1830) {
		if (!egg.egg_intersect && !ch.ch_intersect) {
			gun.setScale(0, 0); //3shan n5fy el gun el 3ady w b3dha nzhr el mayel
			gun_r_l.setScale(1, 1);
			gun_r_l.move(gunvelocity.x, 0);
		}
	}
	//da  3shan lma myb2ash days 3la el right click yrg3 l shkl el gun el 3ady
	else if (event.type == Event::KeyReleased) {
		if (!egg.egg_intersect && !ch.ch_intersect) {
			if (event.key.code == Keyboard::Right) {
				gun.setPosition(gun_r_l.getPosition().x, gun_r_l.getPosition().y);
				gun.setScale(1, 1);
				gun_r_l.setScale(0, 0);
			}
		}
	}
}
void moving_left(Sprite& gun, Sprite& gun_r_l)
{
	if (Keyboard::isKeyPressed(Keyboard::Left) && gun_r_l.getPosition().x > 60) {
		if (!egg.egg_intersect && !ch.ch_intersect) {
			gun.setScale(0, 0);
			gun_r_l.setScale(-1, 1); // el negative 3shan y3ml flip l el sprite bdl m nst5dm sprite tany
			gun_r_l.move(-gunvelocity.x, 0);
		}
	}
	//same as the right movement
	else if (event.type == Event::KeyReleased) {
		if (!egg.egg_intersect && !ch.ch_intersect) {
			if (event.key.code == Keyboard::Left) {
				gun.setPosition(gun_r_l.getPosition().x, gun_r_l.getPosition().y);
				gun.setScale(1, 1);
				gun_r_l.setScale(0, 0);
			}
		}
	}
}
void moving_up(Sprite& gun, Sprite& gun_r_l) {
	if (Keyboard::isKeyPressed(Keyboard::Up) && gun_r_l.getPosition().y > 100) {
		gun.move(0, -gunvelocity.y);
		gun_r_l.setPosition(gun.getPosition().x, gun.getPosition().y);
	}
}
void moving_down(Sprite& gun, Sprite& gun_r_l) {
	if (Keyboard::isKeyPressed(Keyboard::Down) && gun_r_l.getPosition().y < 900) {
		gun.move(0, gunvelocity.y);
		gun_r_l.setPosition(gun.getPosition().x, gun.getPosition().y);
	}
}
void gun_movement(Sprite& gun, Sprite& gun_r_l)
{
	moving_right(gun, gun_r_l);
	moving_left(gun, gun_r_l);
	moving_up(gun, gun_r_l);
	moving_down(gun, gun_r_l);
	if (Keyboard::isKeyPressed(Keyboard::Right) && Keyboard::isKeyPressed(Keyboard::Up)) {
		gun.move(1.3, -0.6);
	}
	if (Keyboard::isKeyPressed(Keyboard::Left) && Keyboard::isKeyPressed(Keyboard::Up)) {
		gun.move(-1.3, -0.6);
	}
	if (Keyboard::isKeyPressed(Keyboard::Right) && Keyboard::isKeyPressed(Keyboard::Down)) {
		gun.move(1.3, 0.6);
	}
	if (Keyboard::isKeyPressed(Keyboard::Left) && Keyboard::isKeyPressed(Keyboard::Down)) {
		gun.move(-1.3, 0.6);
	}
}
void red_chicken_movement() {
	for (int j = 0; j < 30; j++) {
		if (ch.timerr[j] < 0) {
			ch.arrchicken[j].move(ch.xstep[j], 0);
			ch.spawn[j]++;
			ch.spawn[j] = ch.spawn[j] % 4;
			ch.arrchicken[j].setTextureRect(IntRect(ch.spawn[j] * 108.5, 0, 108.5, 113));
			ch.timerr[j] = ch.delayr;
		}
		else {
			ch.timerr[j] -= dt;
		}
	}
	if (ch.arrchicken[29].getPosition().x > 1750) {
		//	awel ma yewsal le goz2 mo3ayan men el screen ben3ks el sign beta3et el xstep 3ashan yero7 el nay7a el tanya
		for (int j = 0; j < 30; j++) {
			ch.xstep[j] = -ch.xstep[j];
			ch.arrchicken[j].move(ch.xstep[j], 0);
		}
	}

	if (ch.arrchicken[0].getPosition().x < -5) {
		for (int j = 0; j < 30; j++) {
			ch.xstep[j] = -ch.xstep[j];
			ch.arrchicken[j].move(ch.xstep[j], 0);
		}
	}
}
void green_chicken_movement() {

	for (int j = 30; j < 60; j++) {
		ch.arrchicken[j].move(ch.xstep[j], 0);
		if (ch.timerg < 0) {
			ch.spawn[j]++;
			ch.spawn[j] = ch.spawn[j] % 10;
			ch.arrchicken[j].setTextureRect(IntRect(ch.spawn[j] * 46.9, 0, 46.9, 38));
			ch.timerg = ch.delayg;
		}
		else {
			ch.timerg -= dt;
		}
	}

	if (ch.arrchicken[30].getPosition().x > 1750) {
		//	awel ma yewsal le goz2 mo3ayan men el screen ben3ks el sign beta3et el xstep 3ashan yero7 el nay7a el tanya
		ch.hitwall = 1;
		for (int j = 30; j < 60; j++) {
			ch.xstep[j] = -ch.xstep[j];
			ch.arrchicken[j].move(ch.xstep[j], 0);
		}
	}
}


//CHICKEN BOSS
void boss_movement(Sprite& chickenboss, float& delay) {
	if (boss.bosstimer < 0) {
		boss.h++;
		boss.h = boss.h % 3;
		chickenboss.setTextureRect(IntRect((boss.h * 314.666), 0, 314.666, 264));
		boss.bosstimer = delay;
	}
	else {
		boss.bosstimer -= dt;
	}
	if (b.BulletCounter < 40) {
		if (chickenboss.getPosition().x > 1700) {
			boss.velocity.x = -(rand() % 1) - 0.5;
		}
		else if (chickenboss.getPosition().x < 200) {
			boss.velocity.x = rand() % 1 + 0.5;
		}
		if (chickenboss.getPosition().y < 5) {
			boss.velocity.y = (rand() % 1) + 0.5;
		}
		if (chickenboss.getPosition().y > 700) {
			boss.velocity.y = -(rand() % 1) - 0.5;
		}

		chickenboss.move(boss.velocity);
	}
}
void gun_with_chickenboss(Sprite& gun, Sprite& gun_r_l, Sprite& explosion1, Sound& exp) {
	if (boss.chickenboss.getGlobalBounds().intersects(gun.getGlobalBounds())) {
		boss.intersect = true;
		exp_position = { gun.getPosition().x,gun.getPosition().y };
	}
	if (boss.intersect) {
		gun_death_nobullet(b.bulletsv);
		boss.exptimer++;
		gun_r_l.setScale(0, 0);
		gun.setScale(0, 0);
		oneegg[0].egg.setScale(0, 0);
		explosion1.setPosition(exp_position);
		explosion1.setScale(1, 1);
		if (boss.exptimer > 450) {
			exp.play();
			healthship--;
			explosion1.setScale(0, 0);
			gun.setScale(1, 1);
			gun.setPosition(900, 900);
			gun_r_l.setPosition(900, 900);
			boss.intersect = false;
			boss.exptimer = 0;

		}
	}
}
void bullet_chickenboss(Sprite& gun, Sprite& gun_r_l, Sprite& explosion1, vector<Sprite>& bulletsv, long long& totalscore, Sound& ch_damdge)
{
	for (int j = 0; j < bulletsv.size(); j++) {
		if (bulletsv[j].getGlobalBounds().intersects(boss.chickenboss.getGlobalBounds())) {
			ch_damdge.play();
			b.bulletind = j;
			b.bulletboss = true; {
				boss.boss_exp_pos = { boss.chickenboss.getPosition().x - 200, boss.chickenboss.getPosition().y - 200 };
				bulletsv[b.bulletind].setScale(0, 0);
				b.BulletCounter++;
			}
		}

		if (b.bulletboss && b.BulletCounter == 40) {
			boss.bossexptimer++;
			boss.chickenboss.setScale(0, 0);
			explosion1.setPosition(boss.boss_exp_pos);
			explosion1.setScale(2, 2);
			if (boss.bossexptimer > 400) {
				totalscore += 200;
				boss.chickenboss.setScale(0, 0);
				explosion1.setScale(0, 0);
				b.bulletboss = false;
				boss.bossexptimer = 0;
				b.BulletCounter = 0;
				boss.bosskilled = true;
			}
		}
	}
}
void gun_with_egg(Sprite& gun, Sprite& gun_r_l, Sprite& explosion1, Sound& exp)
{
	if (gun_r_l.getGlobalBounds().intersects(oneegg[0].egg.getGlobalBounds())) {
		oneegg[0].eggintersect = true;
		oneegg[0].eggexpposition = { gun_r_l.getPosition().x - 150,gun_r_l.getPosition().y - 150 };
	}

	// gunr_l&egg collision
	if (oneegg[0].eggintersect) {
		gun_death_nobullet(b.bulletsv);
		oneegg[0].eggexptimer++;
		gun_r_l.setScale(0, 0);
		gun.setScale(0, 0);
		oneegg[0].egg.setScale(0, 0);
		explosion1.setPosition(oneegg[0].eggexpposition.x, oneegg[0].eggexpposition.y);
		explosion1.setScale(1, 1);
		if (oneegg[0].eggexptimer > 750) {
			exp.play();
			healthship--;
			explosion1.setScale(0, 0);
			gun.setScale(1, 1);
			gun_r_l.setPosition(900, 900);
			gun_r_l.setPosition(900, 900);
			oneegg[0].eggintersect = false;
			oneegg[0].eggexptimer = 0;
		}
	}
}
void egg_random_boss(Clock& eggclock, Sound& egg_fall)
{
	if (eggclock.getElapsedTime().asSeconds() > 3) {
		egg_fall.play();
		oneegg[0].egg.setPosition(boss.chickenboss.getPosition().x, boss.chickenboss.getPosition().y);
		oneegg[0].egg.setScale(1, 1);
		eggclock.restart();
	}
}


//PURPLE BOSS
void purpleboss_movement(float& delay) {
	if (purple.purplebosstimer < 0) {
		purple.f++;
		purple.f = purple.f % 3;
		purple.purpleboss.setTextureRect(IntRect((purple.f * 144), 0, 144, 115));
		purple.purplebosstimer = delay;
		purple.purpleboss.setScale(2.4, 2.4);
	}
	else {
		purple.purplebosstimer -= dt;
	}

	if (b.BulletCounter_purpleBoss < 20) {
		if (purple.purpleboss.getPosition().x > 1700) {
			purple.purple_boss_velocity.x = -(rand() % 1) - 0.5;
		}
		else if (purple.purpleboss.getPosition().x < 200) {
			purple.purple_boss_velocity.x = rand() % 1 + 0.5;
		}
		if (purple.purpleboss.getPosition().y < 5) {
			purple.purple_boss_velocity.y = (rand() % 1) + 0.5;
		}
		if (purple.purpleboss.getPosition().y > 700) {
			purple.purple_boss_velocity.y = -(rand() % 1) - 0.5;
		}

		purple.purpleboss.move(purple.purple_boss_velocity);
	}
}
void gun_with_egg1(Sprite& gun, Sprite& gun_r_l, Sprite arrexplosion[], Sound& exp)
{
	if (gun_r_l.getGlobalBounds().intersects(oneegg[0].egg_frompurple.getGlobalBounds())) {
		oneegg[0].eggintersect_purple = true;
		oneegg[0].eggexpposition_purple = { gun_r_l.getPosition().x - 150,gun_r_l.getPosition().y - 150 };
	}

	// gunr_l&egg collision
	if (oneegg[0].eggintersect_purple) {
		gun_death_nobullet(b.bulletsv);
		oneegg[0].eggexptimer_purple++;
		gun_r_l.setScale(0, 0);
		gun.setScale(0, 0);
		oneegg[0].egg_frompurple.setScale(0, 0);
		arrexplosion[2].setPosition(oneegg[0].eggexpposition_purple.x, oneegg[0].eggexpposition_purple.y);
		arrexplosion[2].setScale(1, 1);
		if (oneegg[0].eggexptimer_purple > 750) {
			exp.play();
			healthship--;
			arrexplosion[2].setScale(0, 0);
			gun_r_l.setScale(1, 1);
			gun_r_l.setPosition(900, 800);
			gun_r_l.setPosition(900, 800);
			oneegg[0].eggintersect_purple = false;
			oneegg[0].eggexptimer_purple = 0;
		}
	}
}
void gun_with_purpleboss(Sprite& gun, Sprite& gun_r_l, Sprite arrexplosion[], Sound& exp) {
	if (purple.purpleboss.getGlobalBounds().intersects(gun.getGlobalBounds())) {
		e.gunintersect_with_purple = true;
		exp_position = { gun.getPosition().x - 100,gun.getPosition().y - 180 };
	}
	if (e.gunintersect_with_purple) {
		e.gun_exptimer_with_purple++;
		gun_death_nobullet(b.bulletsv); // 3shan mytl3sh tal2
		gun.setScale(0, 0);
		gun.move(0, 0);
		arrexplosion[0].setPosition(exp_position.x, exp_position.y);
		arrexplosion[0].setScale(1, 1);

		if (e.gun_exptimer_with_purple > 450) {
			exp.play();
			healthship--;
			arrexplosion[0].setScale(0, 0);
			gun.setScale(1, 1);
			gun.setPosition(900, 800);
			gun_r_l.setPosition(900, 800);
			e.gunintersect_with_purple = false;
			e.gun_exptimer_with_purple = 0;
		}
	}

}
void bullet_with_purpleboss(Sprite& gun, Sprite& gun_r_l, Sprite arrbigexplosion[], vector<Sprite>& bull, Sound& ch_damdge, long long& totalscore) {
	for (int i = 0; i < bull.size(); i++) {
		if (bull[i].getGlobalBounds().intersects(purple.purpleboss.getGlobalBounds())) {
			bull[i].setScale(0, 0);
			totalscore += 200;
			b.BulletCounter_purpleBoss++;
		}
		if (b.BulletCounter_purpleBoss == 20) { // lma ywsl l 20 elfar5a btmot
			b.bullet_purpleboss = true;
			b.ExplosionTimer_purpleboss++;
			purple.purpleboss.move(0, 0);
			arrbigexplosion[0].setPosition(purple.purpleboss.getPosition().x - 200, purple.purpleboss.getPosition().y - 200);
			break;
		}
	}
	if (b.bullet_purpleboss) {
		ch_damdge.play();
		purple.purpleboss.setScale(0, 0);
		arrbigexplosion[0].setScale(2, 2);
		if (b.ExplosionTimer_purpleboss > 100) {
			arrbigexplosion[0].setScale(0, 0);
		}
	}
}


//BLUE BOSS
void blueboss_movement(float& delay2) {
	if (blue.bluebosstimer < 0) {
		blue.j++;
		blue.j = blue.j % 3;
		blue.blueboss.setTextureRect(IntRect((blue.j * 200), 0, 200, 117));
		blue.bluebosstimer = delay2;
		blue.blueboss.setScale(1.8, 1.8);
	}
	else {
		blue.bluebosstimer -= dt;
	}

	if (b.BulletCounter_blueboss < 20)
		if (blue.blueboss.getPosition().x > 1700) {
			blue.blue_boss_velocity.x = -(rand() % 1) - 0.5;
		}
		else if (blue.blueboss.getPosition().x < 200) {
			blue.blue_boss_velocity.x = (rand() % 1) + 0.5;
		}
	if (blue.blueboss.getPosition().y < 5) {
		blue.blue_boss_velocity.y = (rand() % 1) + 0.5;
	}
	if (blue.blueboss.getPosition().y > 700) {
		blue.blue_boss_velocity.y = -(rand() % 1) - 0.5;
	}

	blue.blueboss.move(blue.blue_boss_velocity);
}
void gun_with_egg2(Sprite& gun, Sprite& gun_r_l, Sprite arrexplosion[], Sound& exp)
{
	if (gun_r_l.getGlobalBounds().intersects(oneegg[0].egg_fromblue.getGlobalBounds())) {
		oneegg[0].eggintersect_blue = true;
		oneegg[0].eggexpposition_blue = { gun_r_l.getPosition().x - 150,gun_r_l.getPosition().y - 150 };
	}

	// gunr_l&egg collision
	if (oneegg[0].eggintersect_blue) {
		gun_death_nobullet(b.bulletsv);
		oneegg[0].eggexptimer_blue++;
		gun_r_l.setScale(0, 0);
		gun.setScale(0, 0);
		oneegg[0].egg_fromblue.setScale(0, 0);
		arrexplosion[2].setPosition(oneegg[0].eggexpposition_blue.x, oneegg[0].eggexpposition_blue.y);
		arrexplosion[2].setScale(1, 1);
		if (oneegg[0].eggexptimer_blue > 750) {
			exp.play();
			healthship--;
			arrexplosion[2].setScale(0, 0);
			gun_r_l.setScale(1, 1);
			gun_r_l.setPosition(900, 800);
			gun_r_l.setPosition(900, 800);
			oneegg[0].eggintersect_blue = false;
			oneegg[0].eggexptimer_blue = 0;
		}
	}
}
void gun_with_blueboss(Sprite& gun, Sprite& gun_r_l, Sprite arrexplosion[], Sound& exp) {
	if (blue.blueboss.getGlobalBounds().intersects(gun.getGlobalBounds())) {
		e.gunintersect_with_blue = true;
		exp_position = { gun.getPosition().x - 100,gun.getPosition().y - 180 };
	}
	if (e.gunintersect_with_blue) {
		e.gun_exptimer_with_blue++;
		gun_death_nobullet(b.bulletsv); // 3shan mytl3sh tal2
		gun.setScale(0, 0);
		gun.move(0, 0);
		arrexplosion[1].setPosition(exp_position.x, exp_position.y);
		arrexplosion[1].setScale(1, 1);
		if (e.gun_exptimer_with_blue > 450) {
			healthship--;
			exp.play();
			arrexplosion[1].setScale(0, 0);
			gun.setScale(1, 1);
			gun.setPosition(900, 800);
			gun_r_l.setPosition(900, 800);
			e.gunintersect_with_blue = false;
			e.gun_exptimer_with_blue = 0;
		}
	}

}
void bullet_with_blueboss(Sprite& gun, Sprite& gun_r_l, Sprite arrbigexplosion[], vector<Sprite>& bull, Sound& ch_damdge, long long& totalscore) {
	for (int m = 0; m < bull.size(); m++) {
		if (bull[m].getGlobalBounds().intersects(blue.blueboss.getGlobalBounds())) {
			bull[m].setScale(0, 0);
			totalscore += 200;
			b.BulletCounter_blueboss++;
		}
		if (b.BulletCounter_blueboss == 20) { // lma ywsl l 20 elfar5a btmot
			b.bullet_blueboss = true;
			b.ExplosionTimer_blueboss++;
			blue.blueboss.move(0, 0);
			arrbigexplosion[1].setPosition(blue.blueboss.getPosition().x - 200, blue.blueboss.getPosition().y - 200);
			break;
		}
	}
	if (b.bullet_blueboss) {
		ch_damdge.play();
		blue.blueboss.setScale(0, 0);
		arrbigexplosion[1].setScale(2, 2);
		if (b.ExplosionTimer_blueboss > 100) {
			arrbigexplosion[1].setScale(0, 0);

		}
	}
}

//RANDOM FALLING
void gift_random(Clock& giftclock, Sprite& gift, int x)
{
	if (giftclock.getElapsedTime().asSeconds() > x) { //3obara 3an timer kol 7 sawany binazel gift we el .restart() 3ashan yemna3 el gifts to3od tenzel keter ba3d el 3 sawany
		gift.setScale(1.3, 1.3);
		gift.setPosition(rand() % 1800, 0);
		giftclock.restart();
	}
	gift.move(0, 0.5);
}
void egg_random(Clock& eggclock, Sprite arregg[], int& eggrandom, Sprite arrchicken[], int x, int y, Sound& egg_fall)
{
	if (eggclock.getElapsedTime().asSeconds() > 5) {
		egg_fall.play();
		for (int j = 0; j < 3; j++) {
			arregg[j].setScale(1, 1);
			eggrandom = (rand() % x) + y;
			arregg[eggrandom].setPosition(arrchicken[(rand() % x) + y].getPosition().x, arrchicken[(rand() % x) + y].getPosition().y);
		}
		eggclock.restart();
	}

}
void rock_random(Clock& rockclock, Sprite arrrocks1[], bool& stop)
{

	if (!stop && r.co < 50) {
		if (rockclock.getElapsedTime().asSeconds() > 1) {
			r.rockrandom = rand() % 50;
			float arr[4] = { 0.8,1.2,1.6,1.8 };
			int index = rand() % 4;
			arrrocks1[r.rockrandom].setPosition(rand() % 900, 0);
			arrrocks1[r.rockrandom].setScale(arr[index], arr[index]);
			rockclock.restart();
			r.co++;
		}
	}
	else
	{
		for (int i = 0; i < 50; i++) {
			arrrocks1[i].setScale(0, 0);
		}
	}

}
void eggRandom(Clock& egg1clock, Clock& egg2clock, Sound& egg_fall) {
	if (b.BulletCounter_purpleBoss < 20 && b.BulletCounter_purpleBoss != 0) {
		if (egg1clock.getElapsedTime().asSeconds() > 5) {
			egg_fall.play();
			oneegg[0].egg_frompurple.setPosition(purple.purpleboss.getPosition().x - 20, purple.purpleboss.getPosition().y);
			oneegg[0].egg_frompurple.setScale(1, 1);
			egg1clock.restart();
		}
	}
	if (b.BulletCounter_blueboss < 20 && b.BulletCounter_blueboss != 0) {
		if (egg2clock.getElapsedTime().asSeconds() > 3) {
			egg_fall.play();
			oneegg[0].egg_fromblue.setPosition(blue.blueboss.getPosition().x - 20, blue.blueboss.getPosition().y);
			oneegg[0].egg_fromblue.setScale(1, 1);
			egg2clock.restart();
		}
	}

}







void gameoverr(Text& gameover, long long& totalscore) {
	if (levels <= 5) {


		if (healthship == 0) {

			gameover.setString("gameover");
			gun_death_nobullet(b.bulletsv);

			ofstream offile;
			offile.open("mango.txt", ios::app);
			offile << namee << "    " << totalscore << "    " << "*" << endl;
		}
	}
	if (levels >= 6) {


		if (healthship == 0 && healthship2 == 0) {

			gameover.setString("gameover");
			gun_death_nobullet(b.bulletsv2);
			gun_death_nobullet(b.bulletsv);

			ofstream offile;
			offile.open("mango.txt", ios::app);
			offile << namee << "    " << totalscore << "    " << "*" << endl;
		}
	}

}

//SCOREBOARD
void _history(RenderWindow& window) {

	Texture gameoverbg;
	gameoverbg.loadFromFile("space.jpeg");
	Sprite Gameoverbg(gameoverbg);
	Gameoverbg.setScale(2, 2);


	Font font;
	font.loadFromFile("Baqacents_Semibold.ttf");
	Text text[100];


	Text textt[100];
	for (int i = 0; i < 55; i++)
	{
		text[i].setFont(font);
		text[i].setCharacterSize(100);
		text[i].setFillColor(Color::White);
		text[i].setPosition(100, 100);

	}
	ifstream infile;
	infile.open("mango.txt ", ios::in);

	vector<string> lines;
	string line;

	while (getline(infile, line, '*')) {

		lines.push_back(line);
	}
	for (int i = 1; i < lines.size(); i++)
	{

		text[i].setString(lines[i]);
		text[i].setPosition(50, i * 100);

	}
	while (window.isOpen()) {
		Event event;
		while (window.pollEvent(event)) {
			if (event.type == Event::Closed) {
				window.close();
			}
			if (Keyboard::isKeyPressed(Keyboard::Escape))
			{
				window.close();
			}
			if (Keyboard::isKeyPressed(Keyboard::Up))
			{
				if (text[0].getPosition().y <= 8) {
					for (int i = 0; i < lines.size() + 10; i++) {
						text[i].move(0, 20);
					}
				}
			}
			if (Keyboard::isKeyPressed(Keyboard::Down))
			{
				if (text[lines.size() - 1].getPosition().y >= window.getPosition().y + 1000) {
					for (int i = 0; i < lines.size() + 10; i++) {
						text[i].move(0, -20);
					}
				}
			}


		}
		window.clear();
		window.draw(Gameoverbg);
		for (int i = 1; i < lines.size(); i++)
		{
			window.draw(text[i]);
		}
		window.display();
	}

}



void textscore_bar(Text ourtext[100], int& fontx, int start, int end) {
	for (int i = start; i < end; i++) {
		ourtext[i].setCharacterSize(30);
		ourtext[i].setFillColor(Color::White);
		ourtext[i].setString("   0");
		ourtext[i].setPosition(fontx, 927);
		fontx += 83;
		ourtext[i].setStyle(Text::Bold);
	}
}
void set_text_bar(Text ourtext[], int rocket, int light, int score, long long& totalscore) {
	ourtext[0].setString("  " + to_string(healthship));
	ourtext[1].setString("  " + to_string(rocket));
	ourtext[2].setString("  " + to_string(light));
	ourtext[3].setString("  " + to_string(score));
	ourtext[4].setString("  " + to_string(totalscore));
}


//DRAW
void draw_basic_object(RenderWindow& window, Sprite space, Sprite bar, Sprite bar2) {
	window.clear();
	window.draw(space);
	window.draw(bar);
	window.draw(bar2);
}


//LOSE - WIN
void string_random(Clock& stringclock, Sprite arrpurplestring[], Sprite arrbluestring[], int& stringrandom)
{
	if (stringclock.getElapsedTime().asSeconds() > 0.3) {
		stringrandom = rand() % 100;
		int index = rand() % 4;
		arrpurplestring[stringrandom].setPosition(rand() % 1800, 0);
		arrpurplestring[stringrandom].setScale(0.2, 0.2);
		arrbluestring[stringrandom].setPosition(rand() % 1800, 0);
		arrbluestring[stringrandom].setScale(0.2, 0.2);
		stringclock.restart();
	}

}
void game_winning(Sprite& gun, Sprite& gun_r_l, Sprite& gun2, Sprite& gun2_r_l, Clock& stringclock, Sprite arrpurplestring[], Sprite arrbluestring[], int& stringrandom, Text& win, long long& totalscore, long long& totalscore2) {
	if (levels == 4) {
		if (boss.bosskilled) {
			gun.setScale(0, 0);
			gun_r_l.setScale(0, 0);
			blue.blueboss.setScale(0, 0);
			purple.purpleboss.setScale(0, 0);
			gun_death_nobullet(b.bulletsv);
			string_random(stringclock, arrpurplestring, arrbluestring, stringrandom);
			win.setString(" Winner Winner \n Chicken Dinner");
		}
	}
	else if (levels == 9) {
		if (boss.bosskilled) {
			gun.setScale(0, 0);
			gun_r_l.setScale(0, 0);
			gun2.setScale(0, 0);
			gun2_r_l.setScale(0, 0);
			boss.chickenboss.setScale(0, 0);
			gun_death_nobullet(b.bulletsv);
			string_random(stringclock, arrpurplestring, arrbluestring, stringrandom);
			if (totalscore > totalscore2) {
				win.setString(" Winner Winner \n Chicken Dinner \n        PLAYER 1");
			}
			if (totalscore2 > totalscore) {
				win.setString(" Winner Winner \n Chicken Dinner \n        PLAYER 2");
			}

		}
	}
}

//------------------------------------------------------------------------------------------------------------------------------------------------------------//



//PLAYER 2222222222222
//-------------------------------------------------------------------------------------------------------//
void settextbar2(Text ourtext[], int rocket2, int light2, int score2, long long& totalscore2) {
	ourtext[8].setString("  " + to_string(healthship2));
	ourtext[7].setString("  " + to_string(rocket2));
	ourtext[6].setString("  " + to_string(light2));
	ourtext[5].setString("  " + to_string(score2));
	ourtext[9].setString("  " + to_string(totalscore2));
}
void moving_right2(Sprite& gun2, Sprite& gun2_r_l)
{
	if (Keyboard::isKeyPressed(Keyboard::D) && gun2_r_l.getPosition().x < 1830) {
		if (!egg.egg_intersect2 && !ch.ch_intersect2) {
			gun2.setScale(0, 0); //3shan n5fy el gun el 3ady w b3dha nzhr el mayel
			gun2_r_l.setScale(1,1);
			gun2_r_l.move(gunvelocity.x, 0);
		}
	}
	//da  3shan lma myb2ash days 3la el right click yrg3 l shkl el gun el 3ady
	else if (event.type == Event::KeyReleased) {
		if (!egg.egg_intersect2 && !ch.ch_intersect2) {
			if (event.key.code == Keyboard::D) {
				gun2.setPosition(gun2_r_l.getPosition().x, gun2_r_l.getPosition().y);
				gun2.setScale(1,1);
				gun2_r_l.setScale(0, 0);
			}
		}
	}
}
void moving_left2(Sprite& gun2, Sprite& gun2_r_l)
{
	if (Keyboard::isKeyPressed(Keyboard::A) && gun2_r_l.getPosition().x > 60) {
		if (!egg.egg_intersect2 && !ch.ch_intersect2) {
			gun2.setScale(0, 0);
			gun2_r_l.setScale(-1, 1); // el negative 3shan y3ml flip l el sprite bdl m nst5dm sprite tany
			gun2_r_l.move(-gunvelocity.x, 0);
		}
	}
	//same as the right movement
	else if (event.type == Event::KeyReleased) {
		if (!egg.egg_intersect2 && !ch.ch_intersect2) {
			if (event.key.code == Keyboard::A) {
				gun2.setPosition(gun2_r_l.getPosition().x, gun2_r_l.getPosition().y);
				gun2.setScale(1,1);
				gun2_r_l.setScale(0, 0);
			}
		}
	}
}
void moving_up2(Sprite& gun2, Sprite& gun2_r_l) {
	if (Keyboard::isKeyPressed(Keyboard::W) && gun2_r_l.getPosition().y > 100) {
		gun2.move(0, -gunvelocity.y);
		gun2_r_l.setPosition(gun2.getPosition().x, gun2.getPosition().y);
	}
}
void moving_down2(Sprite& gun2, Sprite& gun2_r_l) {
	if (Keyboard::isKeyPressed(Keyboard::S) && gun2_r_l.getPosition().y < 900) {
		gun2.move(0, gunvelocity.y);
		gun2_r_l.setPosition(gun2.getPosition().x, gun2.getPosition().y);
	}
}
void gun2_movement(Sprite& gun2, Sprite& gun2_r_l)
{
	moving_right2(gun2, gun2_r_l);
	moving_left2(gun2, gun2_r_l);
	moving_up2(gun2, gun2_r_l);
	moving_down2(gun2, gun2_r_l);
	if (Keyboard::isKeyPressed(Keyboard::Right) && Keyboard::isKeyPressed(Keyboard::Up)) {
		gun2.move(1.3, -0.6);
	}
	if (Keyboard::isKeyPressed(Keyboard::Left) && Keyboard::isKeyPressed(Keyboard::Up)) {
		gun2.move(-1.3, -0.6);
	}
	if (Keyboard::isKeyPressed(Keyboard::Right) && Keyboard::isKeyPressed(Keyboard::Down)) {
		gun2.move(1.3, 0.6);
	}
	if (Keyboard::isKeyPressed(Keyboard::Left) && Keyboard::isKeyPressed(Keyboard::Down)) {
		gun2.move(-1.3, 0.6);
	}
}

void gun2_with_chicken(Sprite& gun2, Sprite& gun2_r_l, Sprite& explosion1, int start, int end, Sound& exp) {
	for (int i = start; i < end; i++) {
		if (gun2_r_l.getGlobalBounds().intersects(ch.arrchicken[i].getGlobalBounds())) {
			ch.ch_intersect2 = true;
			ch.ch_index2 = i;
			exp_position = { gun2_r_l.getPosition().x,gun2_r_l.getPosition().y };
		}
	}
	if (ch.ch_intersect2)
	{
		ch.ch_exptimer2++;
		gun2_r_l.setScale(0, 0);
		gun2.setScale(0, 0);
		ch.arrchicken[ch.ch_index2].setScale(0, 0);
		explosion1.setPosition(exp_position);
		explosion1.setScale(1, 1);
		if (ch.ch_exptimer2 > 500) {
			exp.play();
			healthship2--;
			ch.counter++;
			explosion1.setScale(0, 0);
			gun2_r_l.setScale(1,1);
			gun2_r_l.setPosition(760, 830);
			gun2.setPosition(760, 830);
			ch.ch_intersect2 = false;
			ch.ch_exptimer2 = 0;
			g.gained_red_gift2 = false;
			g.gained_green_gift2 = false;
		}
	}
}
void gun2_with_eggs_rocks(Sprite& gun2, Sprite& gun2_r_l, Sprite arregg[], Sprite& explosion1, int start, int end, Sound& exp)
{
	for (int i = start; i < end; i++) {
		if (gun2_r_l.getGlobalBounds().intersects(arregg[i].getGlobalBounds())) {
			egg.egg_intersect2 = true;
			egg.egg_index2 = i;
			exp_position = { gun2_r_l.getPosition().x,gun2_r_l.getPosition().y };
		}
	}
	if (egg.egg_intersect2)
	{
		egg.egg_exptimer2++;
		gun2_r_l.setScale(0, 0);
		gun2.setScale(0, 0);
		arregg[egg.egg_index2].setScale(0, 0);
		explosion1.setPosition(exp_position);
		explosion1.setScale(1, 1);
		if (egg.egg_exptimer2 > 800) {
			exp.play();
			healthship2--;
			explosion1.setScale(0, 0);
			gun2_r_l.setScale(1,1);
			gun2_r_l.setPosition(760, 830);
			gun2.setPosition(760, 830);
			egg.egg_intersect2 = false;
			egg.egg_exptimer2 = 0;
			g.gained_red_gift2 = false;
			g.gained_green_gift2 = false;
		}
	}
}

void one_bullet2(Sprite gun2, Sprite& fire)
{
	fire.setPosition(gun2.getPosition().x - bullet1_position.x, gun2.getPosition().y - bullet1_position.y);
	fire.setScale(1, 1);
	b.bulletsv2.push_back(fire);
}
void shooting_one_bullet2(Sprite& fire, Sprite& gun2, Sprite& gun2_r_l)
{
	if (b.shoottimer2 < 150) {// el far2 ben el tal2a w el b3dha
		b.shoottimer2++;
	}
	if (Keyboard::isKeyPressed(Keyboard::Q) && (b.shoottimer2 >= 150)) {
		b.shoottimer2 = 0; //bnsfr el counter tany 34an ntl3 tal2 gded
		b.shoot2 = true;

		//3shan azbot position el bullet w el gun mayel ymen
		if (Keyboard::isKeyPressed(Keyboard::D)) {
			bullet1_position = { 0,80 };
			one_bullet2(gun2_r_l, fire);
		}
		//3shan azbot position el bullet w el gun mayel shmal
		else if (Keyboard::isKeyPressed(Keyboard::A)) {
			bullet1_position = { -0,80 };
			one_bullet2(gun2_r_l, fire);
		}
		// da f 7alt el gun el 3ady 
		else {
			bullet1_position = { 0,50 };
			one_bullet2(gun2, fire);
		}
	}
	if (b.shoot2) {
		for (int i = 0; i < b.bulletsv2.size(); i++)
			b.bulletsv2[i].move(bulletvelocity);
	}
}
void two_bullets2(Sprite arrfire[], Sprite gun2)
{
	arrfire[0].setPosition(gun2.getPosition().x + bullet1_position.x, gun2.getPosition().y - bullet1_position.y);
	arrfire[1].setPosition(gun2.getPosition().x - bullet2_position.x, gun2.getPosition().y - bullet2_position.y);
	arrfire[0].setScale(1, 1);
	arrfire[1].setScale(1, 1);
	b.bulletsv2.push_back(arrfire[0]);
	b.bulletsv2.push_back(arrfire[1]);
}
void shooting_two_bullets2(Sprite arrfire[], Sprite gun2, Sprite gun2_r_l)
{
	if (b.shoottimer2 < 150) {// el far2 ben el tal2a w el b3dha
		b.shoottimer2++;
	}

	if (Keyboard::isKeyPressed(Keyboard::Q) && (b.shoottimer2 >= 150)) {
		b.shoottimer2 = 0; //bnsfr el counter tany 34an ntl3 tal2 gded
		b.shoot2 = true;

		//3shan azbot position el bullet w el gun mayel ymen
		if (Keyboard::isKeyPressed(Keyboard::D)) {
			bullet1_position = { 20,110 };
			bullet2_position = { 25,110 };
			two_bullets2(arrfire, gun2_r_l);
		}
		//3shan azbot position el bullet w el gun mayel shmal
		else if (Keyboard::isKeyPressed(Keyboard::A)) {
			bullet1_position = { 20,110 };
			bullet2_position = { 25,110 };
			two_bullets2(arrfire, gun2_r_l);
		}
		// da f 7alt el gun el 3ady 
		else {
			bullet1_position = { 26,110 };
			bullet2_position = { 34,110 };
			two_bullets2(arrfire, gun2);

		}
	}
	if (b.shoot2) {
		for (int i = 0; i < b.bulletsv2.size(); i++) {
			b.bulletsv2[i].move(bulletvelocity);
		}
	}
}
void shooting_gain_gifts2(Sprite gun2, Sprite& gift, Sprite& giftgreen, Sprite gun2_r_l, Sprite arrfire[], Sprite fire, Sprite firegreen, Sound& shot, Sound& giftt) {
	if (gun2.getGlobalBounds().intersects(gift.getGlobalBounds()) || gun2_r_l.getGlobalBounds().intersects(gift.getGlobalBounds())) {
		giftt.play();
		gift.setScale(0, 0);
		g.gained_red_gift2 = true;
		g.gained_green_gift2 = false;
	}
	else if (gun2.getGlobalBounds().intersects(giftgreen.getGlobalBounds()) || gun2_r_l.getGlobalBounds().intersects(giftgreen.getGlobalBounds())) {
		giftt.play();
		giftgreen.setScale(0, 0);
		g.gained_green_gift2 = true;
		g.gained_red_gift2 = false;
	}
	if (g.gained_red_gift2) {
		shot.play();
		shooting_two_bullets2(arrfire, gun2, gun2_r_l);
	}
	else if (g.gained_green_gift2) {
		shot.play();
		shooting_one_bullet2(firegreen, gun2, gun2_r_l);
	}
	else {
		shot.play();
		shooting_one_bullet2(fire, gun2, gun2_r_l);
	}

	for (int i = 0; i < b.bulletsv2.size(); i++) {
		if (b.bulletsv2[i].getPosition().y <= 50) {
			b.bulletsv2.erase(b.bulletsv2.begin() + i);
		}
	}
}

void gun2_with_egg(Sprite& gun2, Sprite& gun2_r_l, Sprite& explosion1, Sound& exp)
{
	if (gun2_r_l.getGlobalBounds().intersects(oneegg[0].egg.getGlobalBounds())) {
		oneegg[0].eggintersect = true;
		oneegg[0].eggexpposition = { gun2_r_l.getPosition().x - 150,gun2_r_l.getPosition().y - 150 };
	}

	// gunr_l&egg collision
	if (oneegg[0].eggintersect) {
		gun_death_nobullet(b.bulletsv2);
		oneegg[0].eggexptimer++;
		gun2_r_l.setScale(0, 0);
		gun2.setScale(0, 0);
		oneegg[0].egg.setScale(0, 0);
		explosion1.setPosition(oneegg[0].eggexpposition.x, oneegg[0].eggexpposition.y);
		explosion1.setScale(1, 1);
		if (oneegg[0].eggexptimer > 750) {
			exp.play();
			healthship2--;
			explosion1.setScale(0, 0);
			gun2.setScale(1,1);
			gun2_r_l.setPosition(760, 830);
			oneegg[0].eggintersect = false;
			oneegg[0].eggexptimer = 0;
		}
	}
}


void gun2_with_chickenboss(Sprite& gun2, Sprite& gun2_r_l, Sprite& explosion1, Sound& exp, long long& totalscore2) {
	if (boss.chickenboss.getGlobalBounds().intersects(gun2.getGlobalBounds())) {
		boss.intersect2 = true;
		exp_position = { gun2.getPosition().x,gun2.getPosition().y };
	}
	if (boss.intersect2) {
		gun_death_nobullet(b.bulletsv);
		boss.exptimer2++;
		gun2_r_l.setScale(0, 0);
		gun2.setScale(0, 0);
		oneegg[0].egg.setScale(0, 0);
		explosion1.setPosition(exp_position);
		explosion1.setScale(1, 1);
		if (boss.exptimer2 > 450) {
			exp.play();
			healthship2--;
			totalscore2 += 200;
			explosion1.setScale(0, 0);
			gun2.setScale(1, 1);
			gun2.setPosition(760, 830);
			gun2_r_l.setPosition(760, 830);
			boss.intersect2 = false;
			boss.exptimer2 = 0;

		}
	}
}

//-------------------------------------------------------------------------------------------------------//





//MAIN MENU
//-----------------------------------------------------------------------------------------//
void choose(Text players[2], Sprite& fork, int& levels) {
	if (fork.getGlobalBounds().intersects(players[0].getGlobalBounds())) {

		players[0].setFillColor(Color{ 255, 204, 0 });
		players[1].setFillColor(Color::White);




	}
	else if (fork.getGlobalBounds().intersects(players[1].getGlobalBounds())) {
		players[1].setFillColor(Color{ 255, 204, 0 });
		players[0].setFillColor(Color::White);

	}
	else {
		players[0].setFillColor(Color::White);
		players[1].setFillColor(Color::White);
	}

	if (fork.getGlobalBounds().intersects(players[1].getGlobalBounds()) && Keyboard::isKeyPressed(Keyboard::Enter)) {
		levels = 1;
	}
	if (fork.getGlobalBounds().intersects(players[0].getGlobalBounds()) && Keyboard::isKeyPressed(Keyboard::Enter)) {
		levels = 6;
	}
}
void Back(Text& back, Sprite& fork, int& levels) {
	if (fork.getGlobalBounds().intersects(back.getGlobalBounds())) {

		back.setFillColor(Color{ 255, 204, 0 });

	}
	else {
		back.setFillColor(Color::White);
	}
	if (fork.getGlobalBounds().intersects(back.getGlobalBounds()) && Keyboard::isKeyPressed(Keyboard::Space)) {
		levels = -1;
	}
}
void choose2(Text chooose[3], Sprite& fork, int& levels) {
	if (fork.getGlobalBounds().intersects(chooose[0].getGlobalBounds())) {

		chooose[0].setFillColor(Color{ 255, 204, 0 });
		chooose[1].setFillColor(Color::White);
		chooose[2].setFillColor(Color::White);


	}
	else if (fork.getGlobalBounds().intersects(chooose[1].getGlobalBounds())) {
		chooose[1].setFillColor(Color{ 255, 204, 0 });
		chooose[0].setFillColor(Color::White);
		chooose[2].setFillColor(Color::White);
		chooose[3].setFillColor(Color::White);


	}
	else if (fork.getGlobalBounds().intersects(chooose[2].getGlobalBounds())) {
		chooose[2].setFillColor(Color{ 255, 204, 0 });
		chooose[0].setFillColor(Color::White);
		chooose[1].setFillColor(Color::White);
		chooose[3].setFillColor(Color::White);
	}
	else if (fork.getGlobalBounds().intersects(chooose[3].getGlobalBounds())) {
		chooose[3].setFillColor(Color{ 255, 204, 0 });
		chooose[0].setFillColor(Color::White);
		chooose[1].setFillColor(Color::White);
		chooose[2].setFillColor(Color::White);
	}

	else {
		chooose[0].setFillColor(Color::White);
		chooose[1].setFillColor(Color::White);
		chooose[2].setFillColor(Color::White);
		chooose[3].setFillColor(Color::White);

	}
	if (fork.getGlobalBounds().intersects(chooose[0].getGlobalBounds()) && Keyboard::isKeyPressed(Keyboard::Space)) {
		levels = 0;

	}
	else if (fork.getGlobalBounds().intersects(chooose[2].getGlobalBounds()) && Keyboard::isKeyPressed(Keyboard::Space)) {
		levels = -2;
	}
	else if (fork.getGlobalBounds().intersects(chooose[3].getGlobalBounds()) && Keyboard::isKeyPressed(Keyboard::Space)) {
		levels = -3;
	}


}
void movefork(Sprite& fork) {
	if (Keyboard::isKeyPressed(Keyboard::Right) && fork.getPosition().x < 1830) {
		fork.move(1.5, 0);
	}
	if (Keyboard::isKeyPressed(Keyboard::Left) && fork.getPosition().x > 60) {
		fork.move(-1.5, 0);
	}
	if (Keyboard::isKeyPressed(Keyboard::Up) && fork.getPosition().y > 100) {
		fork.move(0, -1.5);
	}
	if (Keyboard::isKeyPressed(Keyboard::Down) && fork.getPosition().y < 900) {
		fork.move(0, 1.5);
	}
}
void drawsinglechicken(float& timermainmenu, float& delaymainmenu, int& l, Sprite& singlechicken) {

	if (timermainmenu < 0) {
		l++;
		l = l % 8;
		singlechicken.setTextureRect(IntRect(l * (868 / 8), 0, 868 / 8, 113));
		timermainmenu = delaymainmenu;

	}
	else {
		timermainmenu -= dt;
	}
}
//-----------------------------------------------------------------------------------------//










int main()
{

	//window
	RenderWindow window(VideoMode::getDesktopMode(), "Chicken invader");
	Clock gameclock;



	//SPRITES 
	//---------------------------------------------------------------------------------------------------//
	//background
	Texture background;
	background.loadFromFile("space.jpeg");
	Sprite space(background);
	space.setScale(2, 2);

	Texture animatedbackground;
	animatedbackground.loadFromFile("movingspace.jpeg");
	// han7ot 2 sprites
	Sprite movingspace1(animatedbackground);
	Sprite movingspace2(animatedbackground);
	movingspace1.setScale(2, 2);
	movingspace2.setScale(2, 2);
	movingspace2.setPosition(0, movingspace1.getGlobalBounds().height);
	//  speed beta3 el background
	float scrollSpeed = 0.2;

	//ground
	RectangleShape ground;
	ground.setFillColor(Color::Transparent);
	ground.setSize(Vector2f(2000, 100));
	ground.setPosition(0, 1000);

	//spaceship
	Texture ship;
	ship.setSmooth(true);
	ship.loadFromFile("gun.png");
	Sprite gun(ship);
	gun.setScale(1, 1);
	gun.setOrigin(126 / 2, 244 / 2);
	gun.setPosition(900, 900);

	//spaceship right(r) & left(l)
	Texture ship_r_l;
	ship_r_l.loadFromFile("gun right & left.png");
	Sprite gun_r_l(ship_r_l);
	gun_r_l.setScale(0, 0);
	gun_r_l.setOrigin(116 / 2, 251 / 2);
	gun_r_l.setPosition(900, 900);

	//Spaceship 2
	Texture ship2;
	ship2.setSmooth(true);
	ship2.loadFromFile("gun2.png");
	Sprite gun2(ship2);
	gun2.setOrigin(129 / 2, 220 / 2);
	gun2.setPosition(700, 890);

	//spaceship2 right(r) & left(l)
	Texture ship2_r_l;
	ship2_r_l.loadFromFile("gun2_l_r.png");
	Sprite gun2_r_l(ship2_r_l);
	gun2_r_l.setScale(0, 0);
	gun2_r_l.setOrigin(108 / 2, 279 / 2);
	gun2_r_l.setPosition(700, 830);

	//red bullet
	Texture bullets;
	bullets.loadFromFile("fire.png");
	Sprite fire(bullets);
	fire.setOrigin(21 / 2, 73 / 2);
	fire.setScale(0, 0); //3shan kant btzhr fo2 f el corner awel m n3ml run
	Sprite arrfire[2] = { fire,fire };


	//green bullet
	Texture bulletsg;
	bulletsg.loadFromFile("green2.png");
	Sprite firegreen(bulletsg);
	firegreen.setOrigin(17 / 2, 97 / 2);
	firegreen.setScale(0, 0);

	//explosion
	Texture exp1;
	exp1.loadFromFile("expll.png");
	Sprite explosion1(exp1);
	explosion1.setScale(0, 0);
	explosion1.setOrigin(225 / 2, 225 / 2);
	Sprite arrbigexplosion[2];
	Sprite arrexplosion[3];
	for (int i = 0; i < 2; i++) {
		arrbigexplosion[i] = explosion1;
		arrbigexplosion[i].setScale(0, 0);
	}
	for (int i = 0; i < 3; i++) {
		arrexplosion[i] = explosion1;
		arrexplosion[i].setScale(0, 0);
	}

	//damage
	Clock damageclock[150];
	Texture Damege;
	Damege.loadFromFile("damage1.png");
	Sprite damage(Damege);
	damage.scale(0.53, 0.53);
	damage.setPosition(-1000, -1000);//3lshan mtzharsh fe awel el le3ba
	Sprite arrdamage[100];
	for (int j = 0; j < 100; j++) {
		arrdamage[j] = damage;
	}

	//crashed egg
	Clock crashedclock;
	Texture cegg;
	cegg.loadFromFile("crashed egg.png");
	Sprite crashed_egg(cegg);
	crashed_egg.setScale(0, 0);
	Sprite arrcrashed_egg[65];
	for (int i = 0; i < 60; i++) {
		arrcrashed_egg[i] = crashed_egg;
	}

	//redchicken 
	Texture rch;
	rch.loadFromFile("chicken.png");
	Sprite chicken(rch);
	chicken.setPosition(1000, 250);
	chicken.setTextureRect(IntRect(0, 0, 108.5, 108.5));
	chicken.scale(1.1, 1.1);
	rch.setSmooth(true);
	Sprite arrchicken[100];
	for (int i = 0; i < 100; i++) {
		arrchicken[i] = chicken;
	}
	for (int f = 0; f < 30; f++)ch.xstep[f] = 0.3;//elsor3a bta3et el chicken
	for (int f = 30; f < 60; f++)ch.xstep[f] = 0.2;
	setup_red_chicken(chicken);

	//greenchicken
	Texture gch;
	gch.loadFromFile("chickenGreen.png");
	Sprite chickeng(gch);
	chickeng.setPosition(1000, 250);
	chickeng.setTextureRect(IntRect(0, 0, 46.9, 38));
	chickeng.scale(3, 3);
	gch.setSmooth(true);
	for (int i = 0; i < 100; i++) {
		ch.health[i] = 2;
	}
	setup_green_chicken(chickeng);

	//sprite chicken boss1
	Texture bossch1;
	bossch1.loadFromFile("bosspurple.png");
	bossch1.setSmooth(true);
	purple.purpleboss.setTexture(bossch1);
	purple.purpleboss.setPosition(1000, 250);
	purple.purpleboss.setOrigin(Vector2f(144.0f / 2, 115 / 2));
	purple.purpleboss.setTextureRect(IntRect(0, 0, 144.0, 115));
	purple.purpleboss.setScale(1.8, 1.8);

	//sprite chicken boss2

	Texture bossch2;
	bossch2.loadFromFile("bossblue.png");
	bossch2.setSmooth(true);
	blue.blueboss.setTexture(bossch2);
	blue.blueboss.setPosition(1000, 250);
	blue.blueboss.setOrigin(Vector2f(200.0f / 2, 117 / 2));
	blue.blueboss.setTextureRect(IntRect(0, 0, 200, 117));
	blue.blueboss.setScale(1.8, 1.8);

	//chicken boss
	Texture bossch;
	bossch.setSmooth(true);
	bossch.loadFromFile("bosslevel.png");
	boss.chickenboss.setTexture(bossch);
	boss.chickenboss.setPosition(1000, 250);
	boss.chickenboss.setOrigin(314.66f / 2, 264.0 / 2);
	boss.chickenboss.setTextureRect(IntRect(0, 0, 314.66, 264));
	boss.chickenboss.setScale(1.5, 1.5);

	//health bar
	Texture Bar;
	Bar.setSmooth(true);
	Bar.loadFromFile("score bar.png");
	Sprite bar(Bar);
	bar.setPosition(0, 910);
	bar.scale(1, 1);

	//score bar
	Texture Bar2;
	Bar2.setSmooth(true);
	Bar2.loadFromFile("score.png");
	Sprite bar2(Bar2);
	bar2.setPosition(0, -3);
	bar2.scale(1, 1);

	//health bar
	Texture Bar3;
	Bar3.setSmooth(true);
	Bar3.loadFromFile("score bar2.png");
	Sprite bar3(Bar3);
	bar3.setPosition(1910, 910);
	bar3.scale(-1, 1);

	//score bar
	Texture Bar4;
	Bar4.setSmooth(true);
	Bar4.loadFromFile("score2.png");
	Sprite bar4(Bar4);
	bar4.setPosition(1915, -3);
	bar4.scale(-1, 1);

	//TEXT health bar
	Font font;
	font.loadFromFile("Baqacents_Semibold.ttf");
	Text ourtext[10];
	int fontx = 45;//position font 3la el x
	int fontx2 = 1550;
	for (int i = 0; i < 10; i++) {
		ourtext[i].setFont(font);
	}
	//for totalscore for player 1
	ourtext[4].setCharacterSize(35);
	ourtext[4].setFillColor(Color::White);
	ourtext[4].setString("   0");
	ourtext[4].setPosition(15, 0);
	ourtext[4].setStyle(Text::Bold);

	//for totalscore for player 2
	ourtext[9].setCharacterSize(35);
	ourtext[9].setFillColor(Color::White);
	ourtext[9].setString("   0");
	ourtext[9].setPosition(1700, 0);
	ourtext[9].setStyle(Text::Bold);

	textscore_bar(ourtext, fontx, 0, 4);//functtion call text bar
	textscore_bar(ourtext, fontx2, 5, 9);
	
	Clock waveclock[10];
	bool restartWord[10] = { false };


	Font over;
	over.loadFromFile("George.ttf");
	Text gameover;
	gameover.setFont(over);
	gameover.setPosition(550, 300);
	gameover.setFillColor(Color::White);
	gameover.setCharacterSize(150);

	Text win;
	win.setFont(over);
	win.setPosition(400, 250);
	win.setFillColor(Color::White);
	win.setCharacterSize(140);

	//game title
	Font menufont;
	menufont.loadFromFile("InvadersItalic.otf");
	Text title;
	title.setFillColor(Color::White);
   	title.setFont(menufont);
	title.setCharacterSize(75);
	title.setPosition(500, 150);
	//player
	Text players[2];
	for (int i = 0; i < 2; i++) {
		players[i].setFillColor(Color::White);
		players[i].setFont(menufont);
		players[i].setCharacterSize(80);

	}
	players[0].setPosition(840, 470);
	players[1].setPosition(830, 580);




	

	//single chicken
	Texture single;
	single.loadFromFile("chicken.png");
	Sprite singlechicken(single);
	singlechicken.setScale(1.5, 1.5);
	singlechicken.setOrigin(868 / 2, 113 / 2);
	singlechicken.setPosition(2300, 840);
	singlechicken.setTextureRect(IntRect(0, 0, 108.5, 108.5));
	int l = 0;

	//fork
	Texture Fork;
	Fork.loadFromFile("fork2.png");
	Sprite fork(Fork);
	fork.setScale(1, 1);
	fork.setPosition(200, 200);


	//RANDOM FALLING SPRITES
	srand(time(0));

	//Rocks
	Clock rockclock;
	Texture Rocks;
	Rocks.loadFromFile("rock.png");
	Sprite rocks1(Rocks);
	rocks1.setOrigin(75 / 2, 77 / 2);
	Sprite arrrocks1[50];
	for (int i = 0; i < 50; i++) {
		arrrocks1[i] = rocks1;
	}

	//egg
	Clock eggclock;
	Clock egg1clock;
	Clock egg2clock;
	Texture Egg;
	Egg.loadFromFile("egg.png");
	Sprite egg(Egg);
	Sprite arregg[65];
	egg.setPosition(2000, 0);
	for (int i = 0; i < 60; i++) {
		arregg[i] = egg;
	}
	oneegg[0].egg.setTexture(Egg);
	oneegg[0].egg.setScale(0, 0);
	oneegg[0].egg_frompurple.setTexture(Egg);
	oneegg[0].egg_frompurple.setScale(0, 0);
	oneegg[0].egg_fromblue.setTexture(Egg);
	oneegg[0].egg_fromblue.setScale(0, 0);

	//red gift
	Clock giftclock;
	Texture Gift;
	Gift.loadFromFile("gift1.png");
	Sprite gift(Gift);
	gift.setPosition(2000, 0);
	gift.setScale(1.3, 1.3);

	//green gift
	Clock greengiftclock;
	Texture Gift2;
	Gift2.loadFromFile("gift2.png");
	Sprite giftgreen(Gift2);
	giftgreen.setPosition(2000, 0);
	giftgreen.setScale(1.3, 1.3);

	//leg
	Clock legclock[100];
	Texture legch;
	legch.loadFromFile("leg.png");
	Sprite leg(legch);
	leg.setScale(1.2, 1.2);
	leg.setPosition(-10000, -1000);//el rakam kber 3lshan may5btsh fe el ground lma yaa3
	Sprite arrleg[105];
	for (int j = 0; j < 100; j++) {
		arrleg[j] = leg;
	}

	//winning strings
	Clock strings_clock;
	Texture purplestrings;
	purplestrings.loadFromFile("purple string.png");
	Texture bluestrings;
	bluestrings.loadFromFile("blue string.png");
	Sprite purple_strings(purplestrings);
	Sprite blue_strings(bluestrings);
	Sprite arrpurple_string[100];
	Sprite arrblue_string[100];
	for (int k = 0; k < 100; k++) {
		arrpurple_string[k] = purple_strings;
		arrblue_string[k] = blue_strings;
		arrpurple_string[k].setScale(0, 0);
		arrblue_string[k].setScale(0, 0);
	}
	//---------------------------------------------------------------------------------------------------//


	// text PAUSE menue 
	Font pausemenue;
	pausemenue.loadFromFile("InvadersItalic.otf");
	Text pausefont;
	pausefont.setFont(pausemenue);
	pausefont.setPosition(800, 490);
	pausefont.setCharacterSize(110);


	// logo 
	Texture pauselogo;
	pauselogo.loadFromFile("ChickenInvadersLogo.png");
	Sprite plogo(pauselogo);
	plogo.setPosition(550, 50);
	plogo.setScale(0.75, 0.75);

	//PAUSE button

	

	// volume bar
	Texture volume[11];
	volume[0].loadFromFile("v 0.png");
	volume[1].loadFromFile("v 1.png");
	volume[2].loadFromFile("v 2.png");
	volume[3].loadFromFile("v 3.png");
	volume[4].loadFromFile("v 4.png");
	volume[5].loadFromFile("v 5.png");
	volume[6].loadFromFile("v 6.png");
	volume[7].loadFromFile("v 7.png");
	volume[8].loadFromFile("v 8.png");
	volume[9].loadFromFile("v 9.png");

	Sprite v[11];
	for (int i = 0; i < 10; i++) {
		v[i].setTexture(volume[i]);
		v[i].setPosition(625, 800);
	}

	//SOUNDS
	SoundBuffer ourBuffer;
	ourBuffer.loadFromFile("game.wav");
	Sound ourSound;
	ourSound.setBuffer(ourBuffer);
	ourSound.setVolume(volumee);

	SoundBuffer ourBuffer2;
	ourBuffer2.loadFromFile("Crash_egg.wav");
	Sound cracked_egg;
	cracked_egg.setBuffer(ourBuffer2);
	cracked_egg.setVolume(150);

	SoundBuffer ourBuffer3;
	ourBuffer3.loadFromFile("gift.wav");
	Sound giftt;
	giftt.setBuffer(ourBuffer3);
	giftt.setVolume(20);

	SoundBuffer ourBuffer5;
	ourBuffer5.loadFromFile("explosion.wav");
	Sound exp;
	exp.setBuffer(ourBuffer5);
	exp.setVolume(70);

	SoundBuffer ourBuffer6;
	ourBuffer6.loadFromFile("Egg_fall.wav");
	Sound egg_fall;
	egg_fall.setBuffer(ourBuffer6);
	egg_fall.setVolume(100);

	SoundBuffer ourBuffer7;
	ourBuffer7.loadFromFile("Shooting.wav");
	Sound shot;
	shot.setBuffer(ourBuffer7);
	shot.setVolume(0);

	SoundBuffer ourBuffer8;
	ourBuffer8.loadFromFile("Boss_scream.wav");
	Sound Boss_scream;
	Boss_scream.setBuffer(ourBuffer8);
	Boss_scream.setVolume(100);

	SoundBuffer ourBuffer9;
	ourBuffer9.loadFromFile("Eating_leg.wav");
	Sound Eating_leg;
	Eating_leg.setBuffer(ourBuffer9);
	Eating_leg.setVolume(1000);

	SoundBuffer ourBuffer10;
	ourBuffer10.loadFromFile("chicken dam.wav");
	Sound ch_damdge;
	ch_damdge.setBuffer(ourBuffer10);
	ch_damdge.setVolume(100);

	SoundBuffer ourBuffer11;
	ourBuffer11.loadFromFile("chicken dam.wav");
	Sound rockexp;
	rockexp.setBuffer(ourBuffer7);
	rockexp.setVolume(70);


	RectangleShape frame;
	frame.setFillColor(Color::White);
	frame.setSize(Vector2f(600, 10));
	frame.setPosition(100, 100);

	RectangleShape frame2;
	frame2.setFillColor(Color::White);
	frame2.setSize(Vector2f(600, 10));
	frame2.setPosition(100, 850);
	//-------------------------------------------------------------------------------//

	Text chooose[4];
	for (int i = 0; i < 4; i++) {
		chooose[i].setFillColor(Color::White);
		chooose[i].setFont(menufont);
		chooose[i].setCharacterSize(80);

	}
	chooose[0].setPosition(850, 470);
	chooose[1].setPosition(830, 580);
	chooose[2].setPosition(830, 690);
	chooose[3].setPosition(780, 800);


	//player button
	Texture Button;
	Button.loadFromFile("border3.png");
	Sprite button1(Button);
	button1.setPosition(750, 450);
	button1.setScale(0.5, 1);

	Sprite button2(Button);
	button2.setPosition(750, 560);
	button2.setScale(0.5, 1);

	//---------------------------------------------------------------------//

	Sprite button4(Button);
	button4.setPosition(750, 670);
	button4.setScale(0.5, 1);

	Sprite button5(Button);
	button5.setPosition(750, 780);
	button5.setScale(0.5, 1);

	Sprite button3(Button);
	button3.setPosition(650, 500);
	button3.setScale(0.75, 1);
	// back button
	Sprite button6(Button);
	button6.setPosition(1480, 840);
	button6.setScale(0.5, 1);

	Text back;
	back.setFont(menufont);
	back.setCharacterSize(77);
	back.setPosition(1580, 860);

	Text wave[6];
	Font wavefont;
	wavefont.loadFromFile("Bullpen3D.ttf");
	for (int i = 0; i < 6; i++) {
		wave[i].setFillColor(Color::White);
		wave[i].setFont(wavefont);
		wave[i].setStyle(Text::Bold);
		wave[i].setCharacterSize(180);
		wave[i].setPosition(-50, 300);
	}


	Text textt[7];
	for (int i = 0; i < 55; i++)
	{
		textt[i].setFont(wavefont);
		textt[i].setCharacterSize(80);
		textt[i].setFillColor(Color::White);
	}
	textt[0].setPosition(100, 100);
	textt[1].setPosition(100, 200);
	textt[2].setPosition(100, 300);
	textt[3].setPosition(100, 400);
	textt[4].setPosition(100, 500);
	textt[5].setPosition(100, 600);
	textt[6].setPosition(100, 700);


	textt[0].setString("Mariam Galal");
	textt[1].setString("Menna Sokkar");
	textt[2].setString("Roaa Lotfy");
	textt[3].setString("Farha Ahmed");
	textt[4].setString("Fagr Ashraf");
	textt[5].setString("Omar Hassan");
	textt[6].setString("Zeyad Yasser");


	// how to play bg
	Texture howbg;
	howbg.loadFromFile("howtoplay2.jpg");
	Sprite howtoplay(howbg);
	howtoplay.setScale(1.7, 1.7);


	//VARIABLES
	//------------------------------------------------------------//
	int eggrandom = 0;
	int score = 0;//bt7seb intersect m3a el chicken w el gun
	int rocket = 0;//lma el score =50 btzed one and score=0
	int light = 0;//3addan el hadaya
	int string__random = 0;
	int start1 = 0, end1 = 29;
	int start2 = 30, end2 = 59;
	long long totalscore = 0;
	float delayboss = 0.07;
	float delay_purple_boss;
	float delay_blue_boss;
	bool stop = false;

	//for second player
	int score2 = 0;//bt7seb intersect m3a el chicken w el gun
	int rocket2 = 0;//lma el score =50 btzed one and score=0
	int light2 = 0;//3addan el hadaya
	long long totalscore2 = 0;
	float timermainmenu = 0;
	float delaymainmenu = 0.5;
	int stringrandom = 0;
	int chooseplater = 0;
	//------------------------------------------------------------//





	//GAME LOOP

	while (window.isOpen()) {
		gameclock.restart();
		while (window.pollEvent(event)) {
			if (event.type == Event::Closed) {
				window.close();
			}
			if (event.type == Event::KeyPressed) {

				if (event.key.code == Keyboard::P) {
					if (paused)
						paused = false;
					if (!paused)
						paused = true;

				}
				if (event.key.code == Keyboard::H) {
					if (volumee + 10 <= 90) {
						volumee += 10;

					}
				}
				if (event.key.code == Keyboard::L) {
					if (volumee - 10 >= 0) {
						volumee -= 10;

					}

				}

			}
			ourSound.setVolume(volumee);

		}

		//level-3
		//----------------------------------------------------------------------------------------------------------------------//
		if (levels == -3) {
			movefork(fork);
			Back(back, fork, levels);

			back.setString("Back");


			window.clear();
			window.draw(howtoplay);
			window.draw(button6);
			window.draw(back);
			window.draw(fork);
			window.display();
		}


		//Level -2 mainmenu1
		// --------------------------------------------------------------------------------------------------------------------//
		if (levels == -2) {

			movefork(fork);
			Back(back, fork, levels);

			back.setString("Back");
			window.clear();
			movingbackground(0.1, movingspace1, movingspace2);
			window.draw(movingspace1);
			window.draw(movingspace2);
			for (int i = 0; i < 7; i++)
			{
				window.draw(textt[i]);
			}
			window.draw(button6);
			window.draw(back);
			window.draw(frame);
			window.draw(frame2);
			window.draw(fork);
			window.display();
		}


		//Level -1 mainmenu1
		// -------------------------------------------------------------------------------------------------------------------//
		if (levels == -1) {
			drawsinglechicken(timermainmenu, delaymainmenu, l, singlechicken);
			movefork(fork);
			choose2(chooose, fork, levels);
			chooose[0].setString(" Play");
			chooose[1].setString("History");
			window.clear();
			movingbackground(0.1, movingspace1, movingspace2);
			window.draw(movingspace1);
			window.draw(movingspace2);
			window.draw(button1);
			window.draw(button4);
			window.draw(button5);
			window.draw(button2);
			for (int i = 0; i < 4; i++) {
				window.draw(chooose[i]);
			}
			//window.draw(Gtitle);
			window.draw(plogo);
			window.draw(fork);
			window.draw(singlechicken);
			window.display();
			dt = gameclock.getElapsedTime().asSeconds();
			chooose[2].setString("Credits");
			chooose[3].setString("How To Play?");
		}


		//LEVEL 0 MainMemu2
		//-------------------------------------------------------------------------------------------------------------------//
		if (levels == 0) {


			drawsinglechicken(timermainmenu, delaymainmenu, l, singlechicken);
			movefork(fork);
			choose(players, fork, levels);


			players[0].setString("2 players ");
			players[1].setString("1 player");



			window.clear();
			movingbackground(0.1, movingspace1, movingspace2);
			window.draw(movingspace1);
			window.draw(movingspace2);
			window.draw(button1);
			window.draw(button2);
			for (int i = 0; i < 2; i++) {
				window.draw(players[i]);
			}
			window.draw(plogo);
			window.draw(title);
			window.draw(fork);
			window.draw(singlechicken);
			window.draw(title);
			window.display();
			dt = gameclock.getElapsedTime().asSeconds();

		}


		if (!paused) {
			ourSound.play();
			ourSound.setVolume(volumee);

			//LEVEL 1
			//-------------------------------------------------------------------------------------------------------------------//
			if (healthship == 0) {
				_history(window);
			}





			if (levels == 1) {
				if (restartWord[0] == false) {
					waveclock[0].restart();
					restartWord[0] = true;
				}
				if (waveclock[0].getElapsedTime().asSeconds() < 3) {
					wave[0].move(0.5, 0);
					draw_basic_object(window, space, bar, bar2);
					window.draw(wave[0]);
					window.display();
					wave[0].setString(" Wave  " + to_string(1));
					wave[0].setScale(1, 1);
				}

				else {
					//MOVEMENT
					gun_movement(gun, gun_r_l);
					red_chicken_movement();

					//COLLISIONS
					//shooting bullets & collision with gifts
					shooting_gain_gifts(gun, gift, giftgreen, gun_r_l, arrfire, fire, firegreen, shot, giftt);
					//gun & chicken collision
					gun_with_chickens(gun_r_l, gun, explosion1, 0, 30, exp, totalscore);
					//gun_r_l & chicken collision
					gun_with_chickens(gun, gun_r_l, explosion1, 0, 30, exp, totalscore);
					//gun & egg collision
					gun_with_eggs_rocks(gun_r_l, gun, arregg, explosion1, 0, 30, exp);
					//gun_r_l & egg collision
					gun_with_eggs_rocks(gun, gun_r_l, arregg, explosion1, 0, 30, exp);
					//killing chicken
					killing_red_chicken(arrleg, totalscore, b.bulletsv, ch_damdge);
					//chicken explosion
					set_damage(arrdamage, damageclock, start1, end1);
					//leg counter
					get_chicken_leg(gun, gun_r_l, arrleg, score, start1, end1, totalscore, rocket, Eating_leg);
					//leg _ ground
					leg_with_ground(arrleg, ground, legclock, 0, 30);
					//egg_ground
					egg_with_ground(arregg, ground, arrcrashed_egg, crashedclock, 0, 30, cracked_egg);

					//RANDOM
					gift_random(giftclock, gift, 15);
					gift_random(greengiftclock, giftgreen, 25);
					egg_random(eggclock, arregg, eggrandom, ch.arrchicken, 30, 0, egg_fall);

					gameoverr(gameover, totalscore);


					//DRAWING OBJECTS
					window.clear();
					movingbackground(0.1, movingspace1, movingspace2);
					window.draw(movingspace1);
					window.draw(movingspace2);
					window.draw(gift);
					window.draw(giftgreen);
					for (int i = 0; i < 30; i++) {
						window.draw(arrdamage[i]);
						window.draw(arrcrashed_egg[i]);
						window.draw(arrleg[i]);
						window.draw(arregg[i]);
						arregg[i].move(0, 0.5);
						window.draw(ch.arrchicken[i]);
						ch.arrchicken[i].move(ch.xstep[i], 0);
					}
					for (int i = 0; i < b.bulletsv.size(); i++) {
						window.draw(b.bulletsv[i]);
					}
					window.draw(gun);
					window.draw(gun_r_l);
					window.draw(bar);
					window.draw(bar2);
					window.draw(ground);
					window.draw(explosion1);
					window.draw(gameover);
					for (int i = 0; i < 5; i++) {
						window.draw(ourtext[i]);
					}
					window.display();
					set_text_bar(ourtext, rocket, light, score, totalscore);


				}
			}
			//-------------------------------------------------------------------------------------------------------------------//
			if (ch.counter == 30) levels = 2;




			//LEVEL 2
			//-------------------------------------------------------------------------------------------------------------------//
			if (healthship == 0) {
				_history(window);
			}

			if (levels == 2) {
				if (restartWord[1] == false) {
					waveclock[1].restart();
					restartWord[1] = true;
				}
				if (waveclock[1].getElapsedTime().asSeconds() < 3) {
					wave[1].move(0.5, 0);
					gun_movement(gun, gun_r_l);
					draw_basic_object(window, space, bar, bar2);
					window.draw(gun);
					window.draw(gun_r_l);
					window.draw(wave[1]);
					window.display();
					wave[1].setString(" Wave  " + to_string(2));
					wave[1].setScale(1, 1);
				}

				else {
					//MOVEMENT
					gun_movement(gun, gun_r_l);
					//chicken
					if (ch.hitwall == 0) {
						green_chicken_movement();
					}
					else if (ch.hitwall == 1) {
						green_chicken_movement();
						if (ch.arrchicken[59].getPosition().x < -5) {
							for (int j = 30; j < 60; j++) {
								ch.xstep[j] = -ch.xstep[j];
								ch.arrchicken[j].move(ch.xstep[j], 0);
							}
						}
					}

					//COLLISIONS
					//shooting bullets & collision with gifts
					shooting_gain_gifts(gun, gift, giftgreen, gun_r_l, arrfire, fire, firegreen, shot, giftt);
					//gun_r_l with chicken
					gun_with_chickens(gun, gun_r_l, explosion1, 30, 60, exp, totalscore);
					//gun with chickens
					gun_with_chickens(gun_r_l, gun, explosion1, 30, 60, exp, totalscore);
					//gun & egg collision
					gun_with_eggs_rocks(gun_r_l, gun, arregg, explosion1, 30, 60, exp);
					//gun_r_l & egg collision
					gun_with_eggs_rocks(gun, gun_r_l, arregg, explosion1, 30, 60, exp);
					//killing chicken
					killing_green_chicken(arrleg, totalscore, b.bulletsv, ch_damdge);
					//chicken explosion
					set_damage(arrdamage, damageclock, start2, end2);
					//leg collision
					get_chicken_leg(gun, gun_r_l, arrleg, score, start2, end2, totalscore, rocket, Eating_leg);
					//leg-ground
					leg_with_ground(arrleg, ground, legclock, 30, 60);
					//egg_ground
					egg_with_ground(arregg, ground, arrcrashed_egg, crashedclock, 30, 60, cracked_egg);

					//RANDOM
					egg_random(eggclock, arregg, eggrandom, ch.arrchicken, 30, 30, egg_fall);
					gift_random(giftclock, gift, 25);
					gift_random(greengiftclock, giftgreen, 40);

					gameoverr(gameover, totalscore);


					//DRAWING OBJECTS
					window.clear();
					movingbackground(0.1, movingspace1, movingspace2);
					window.draw(movingspace1);
					window.draw(movingspace2);
					window.draw(gift);
					window.draw(giftgreen);
					for (int i = 30; i < 60; i++) {
						window.draw(arrdamage[i]);
						window.draw(arrleg[i]);
						window.draw(arrcrashed_egg[i]);
						window.draw(arregg[i]);
						window.draw(ch.arrchicken[i]);
						ch.arrchicken[i].move(ch.xstep[i], 0);
						arregg[i].move(0, 0.5);

					}
					for (int i = 0; i < b.bulletsv.size(); i++) {
						window.draw(b.bulletsv[i]);
					}
					window.draw(ground);
					window.draw(explosion1);
					window.draw(gun);
					window.draw(gun_r_l);
					window.draw(bar);
					window.draw(bar2);
					for (int i = 0; i < 5; i++) {
						window.draw(ourtext[i]);
					}
					window.draw(gameover);
					window.display();
					set_text_bar(ourtext, rocket, light, score, totalscore);
				}
			}
			//-------------------------------------------------------------------------------------------------------------------//
			if (ch.counter == 60)  levels = 3;




			//LEVEL 3
			//-------------------------------------------------------------------------------------------------------------------//
			if (healthship == 0) {
				_history(window);
			}

			if (levels == 3) {
				if (restartWord[2] == false) {
					waveclock[2].restart();
					restartWord[2] = true;
				}
				if (waveclock[2].getElapsedTime().asSeconds() < 3) {
					wave[2].move(0.5, 0);
					gun_movement(gun, gun_r_l);
					draw_basic_object(window, space, bar, bar2);
					window.draw(gun);
					window.draw(gun_r_l);
					window.draw(wave[2]);
					window.display();
					wave[2].setString(" Wave  " + to_string(3));
					wave[2].setScale(1, 1);
				}
				else {
					//MOVEMENT
					gun_movement(gun, gun_r_l);
					// shooting bullets & collision with gifts
					shooting_gain_gifts(gun, gift, giftgreen, gun_r_l, arrfire, fire, firegreen, shot, giftt);
					//bullets with rocks 
					smash_rocks(arrrocks1, explosion1, fire, b.bulletsv, totalscore, rockexp);
					//gun & rocks 
					gun_with_eggs_rocks(gun_r_l, gun, arrrocks1, explosion1, 0, 50, exp);
					//gun_r_l & rocks
					gun_with_eggs_rocks(gun, gun_r_l, arrrocks1, explosion1, 0, 50, exp);
					//falling rocks
					rock_random(rockclock, arrrocks1, stop);

					gameoverr(gameover, totalscore);


					// DRAWING OBJECTS
					window.clear();
					movingbackground(0.1, movingspace1, movingspace2);
					window.draw(movingspace1);
					window.draw(movingspace2);
					for (int i = 0; i < b.bulletsv.size(); i++) {
						window.draw(b.bulletsv[i]);
					}
					for (int j = 0; j < 50; j++) {
						window.draw(arrrocks1[j]);
						arrrocks1[j].move(0.2, 0.2);
						arrrocks1[j].rotate(0.05);
					}
					window.draw(gun);
					window.draw(gun_r_l);
					window.draw(bar);
					window.draw(bar2);
					window.draw(explosion1);
					for (int i = 0; i < 5; i++) {
						window.draw(ourtext[i]);
					}
					window.draw(gameover);
					window.display();
					set_text_bar(ourtext, rocket, light, score, totalscore);
				}
			}
			dt = gameclock.getElapsedTime().asSeconds();
			//-------------------------------------------------------------------------------------------------------------------//
			if (r.rocks_counter == 10) { levels = 4;  stop = true;  break; }
			if (levels > 3)break;
		}
		if (paused) {
			if (Keyboard::isKeyPressed(Keyboard::R)) {
				paused = false;

			}

			pausefont.setString("resume");

			int vol = volumee / 10;
			window.clear();
			window.draw(space);
			window.draw(plogo);
			window.draw(button3);
			window.draw(pausefont);
			window.draw(v[vol]);
			window.display();
			dt = gameclock.getElapsedTime().asSeconds();
		}
	}



	while (window.isOpen()) {
		gameclock.restart();
		while (window.pollEvent(event)) {
			if (event.type == Event::Closed) {
				window.close();
			}
			if (event.type == Event::KeyPressed) {

				if (event.key.code == Keyboard::P) {
					if (paused)
						paused = false;
					if (!paused)
						paused = true;

				}
				if (event.key.code == Keyboard::H) {
					if (volumee + 10 <= 90) {
						volumee += 10;

					}
				}
				if (event.key.code == Keyboard::L) {
					if (volumee - 10 >= 0) {
						volumee -= 10;

					}

				}

			}
			ourSound.setVolume(volumee);

		}
		if (!paused) {
			ourSound.play();
			ourSound.setVolume(volumee);

			//LEVEL 4
			//-------------------------------------------------------------------------------------------------------------------//
			if (healthship == 0) {
				_history(window);
			}

			if (levels == 4) {
				Boss_scream.play();
				if (restartWord[3] == false) {
					waveclock[3].restart();
					restartWord[3] = true;
				}
				if (waveclock[3].getElapsedTime().asSeconds() < 3) {
					wave[3].move(0.5, 0);
					gun_movement(gun, gun_r_l);
					draw_basic_object(window, space, bar, bar2);
					window.draw(gun);
					window.draw(gun_r_l);
					window.draw(wave[3]);
					window.display();
					wave[3].setString(" Wave  " + to_string(4));
					wave[3].setScale(1, 1);
				}

				else {
					//MOVEMENT
					gun_movement(gun, gun_r_l);
					boss_movement(boss.chickenboss, delayboss);

					//COLLISIONS
					//shooting
					shooting_gain_gifts(gun, gift, giftgreen, gun_r_l, arrfire, fire, firegreen, shot, giftt);
					//gun & egg collision
					gun_with_egg(gun_r_l, gun, explosion1, exp);
					//gun_r_l & egg collision
					gun_with_egg(gun, gun_r_l, explosion1, exp);
					//gun with chickens
					gun_with_chickenboss(gun_r_l, gun, explosion1, exp);
					//gun_r_l with chickens
					gun_with_chickenboss(gun, gun_r_l, explosion1, exp);
					//chicken boss collision
					bullet_chickenboss(gun, gun_r_l, explosion1, b.bulletsv, totalscore, ch_damdge);
					//egg-ground
					egg_with_ground(arregg, ground, arrcrashed_egg, crashedclock, 0, 30, cracked_egg);
					//falling eggs
					egg_random_boss(eggclock, egg_fall);

					gameoverr(gameover, totalscore);
					game_winning(gun, gun_r_l, gun2, gun2_r_l, strings_clock, arrpurple_string, arrblue_string, string__random, win, totalscore, totalscore2);


					//DRAWING OBJECTS
					window.clear();
					movingbackground(0.1, movingspace1, movingspace2);
					window.draw(movingspace1);
					window.draw(movingspace2);
					for (int i = 0; i < 30; i++) {
						window.draw(arrcrashed_egg[i]);
					}
					for (int i = 0; i < b.bulletsv.size(); i++) {
						window.draw(b.bulletsv[i]);
					}
					window.draw(gun);
					window.draw(gun_r_l);
					window.draw(oneegg[0].egg);
					oneegg[0].egg.move(0, 0.5);
					window.draw(boss.chickenboss);
					window.draw(bar);
					window.draw(bar2);
					window.draw(explosion1);
					for (int i = 0; i < 5; i++) {
						window.draw(ourtext[i]);
					}
					/*for (int i = 0; i < 100; i++) {
						window.draw(arrpurple_string[i]);
						window.draw(arrblue_string[i]);
						arrpurple_string[i].move(0, 0.5);
						arrblue_string[i].move(0, 0.5);
					}

					window.draw(win);*/
					window.draw(gameover);
					window.display();
					set_text_bar(ourtext, rocket, light, score, totalscore);
				}
			}
			//-------------------------------------------------------------------------------------------------------------------//



			if (levels > 4)break;
			//-----------------------------------------------------------------------------------------------------------------/--//
		}
		if (paused) {
			if (Keyboard::isKeyPressed(Keyboard::R)) {
				paused = false;

			}

			pausefont.setString("resume");

			int vol = volumee / 10;
			cout << vol << endl;
			window.clear();
			//window.draw(playbutton);
			window.draw(space);
			window.draw(plogo);
			window.draw(button3);
			window.draw(pausefont);
			window.draw(v[vol]);
			window.display();
			dt = gameclock.getElapsedTime().asSeconds();
		}
	}






	while (window.isOpen()) {
		gameclock.restart();
		while (window.pollEvent(event)) {
			if (event.type == Event::Closed) {
				window.close();
			}
			if (event.type == Event::KeyPressed) {

				if (event.key.code == Keyboard::P) {
					if (paused)
						paused = false;
					if (!paused)
						paused = true;

				}
				if (event.key.code == Keyboard::H) {
					if (volumee + 10 <= 90) {
						volumee += 10;

					}
				}
				if (event.key.code == Keyboard::L) {
					if (volumee - 10 >= 0) {
						volumee -= 10;

					}

				}
			}
			ourSound.setVolume(volumee);

		}
		if (!paused) {
			ourSound.play();
			ourSound.setVolume(volumee);

			//levels2
			if (levels == 6) {
				if (restartWord[0] == false) {
					waveclock[0].restart();
					restartWord[0] = true;
				}

				if (waveclock[0].getElapsedTime().asSeconds() < 3) {
					wave[0].move(0.5, 0);
					draw_basic_object(window, space, bar, bar2);
					window.draw(wave[0]);
					window.draw(bar3);
					window.draw(bar4);
					window.display();
					wave[0].setString(" Wave  " + to_string(1));
					wave[0].setScale(1, 1);
				}

				else {
					//movement
					gun_movement(gun, gun_r_l);
					gun2_movement(gun2, gun2_r_l);
					red_chicken_movement();
					//collisions
					//shooting bullets & collision with gifts
					shooting_gain_gifts(gun, gift, giftgreen, gun_r_l, arrfire, fire, firegreen, shot, giftt);
					shooting_gain_gifts2(gun2, gift, giftgreen, gun2_r_l, arrfire, fire, firegreen, shot, giftt);
					//gun & chicken collision
					gun_with_chickens(gun_r_l, gun, explosion1, 0, 30, exp, totalscore);
					//gun_r_l & chicken collision
					gun_with_chickens(gun, gun_r_l, explosion1, 0, 30, exp, totalscore);

					gun2_with_chicken(gun2, gun2_r_l, explosion1, 0, 30, exp);
					gun2_with_chicken(gun2_r_l, gun2, explosion1, 0, 30, exp);

					//gun & egg collision
					gun_with_eggs_rocks(gun_r_l, gun, arregg, explosion1, 0, 30, exp);
					gun2_with_eggs_rocks(gun2_r_l, gun2, arregg, explosion1, 0, 30, exp);

					//gun_r_l & egg collision
					gun_with_eggs_rocks(gun, gun_r_l, arregg, explosion1, 0, 30, exp);
					gun2_with_eggs_rocks(gun2, gun2_r_l, arregg, explosion1, 0, 30, exp);

					//killing chicken
					killing_red_chicken(arrleg, totalscore, b.bulletsv, ch_damdge);
					killing_red_chicken(arrleg, totalscore2, b.bulletsv2, ch_damdge);

					//chicken explosion
					set_damage(arrdamage, damageclock, start1, end1);
					//leg collision
					get_chicken_leg(gun, gun_r_l, arrleg, score, start1, end1, totalscore, rocket, Eating_leg);
					get_chicken_leg(gun2, gun2_r_l, arrleg, score2, start1, end1, totalscore2, rocket2, Eating_leg);
					//leg _ ground
					leg_with_ground(arrleg, ground, legclock, 0, 30);

					//health
					//random
					gift_random(giftclock, gift, 10);
					gift_random(greengiftclock, giftgreen, 23);
					egg_random(eggclock, arregg, eggrandom, ch.arrchicken, 30, 0, egg_fall);
					gameoverr(gameover, totalscore);

					egg_with_ground(arregg, ground, arrcrashed_egg, crashedclock, 0, 30, cracked_egg);



					//DRAWING OBJECTS
					window.clear();
					window.draw(space);
					window.draw(gift);
					window.draw(giftgreen);
					for (int i = 0; i < 30; i++) {
						window.draw(arrdamage[i]);
						window.draw(arrcrashed_egg[i]);
						window.draw(arregg[i]);
						arregg[i].move(0, 0.5);
						window.draw(ch.arrchicken[i]);
						ch.arrchicken[i].move(ch.xstep[i], 0);
						window.draw(arrleg[i]);
					}
					for (int i = 0; i < b.bulletsv.size(); i++) {
						window.draw(b.bulletsv[i]);
					}
					for (int i = 0; i < b.bulletsv2.size(); i++) {
						window.draw(b.bulletsv2[i]);
					}
					window.draw(gun);
					window.draw(gun_r_l);
					window.draw(gun2);
					window.draw(gun2_r_l);
					window.draw(bar);
					window.draw(bar2);
					window.draw(bar3);
					window.draw(bar4);
					window.draw(ground);
					window.draw(explosion1);
					for (int i = 0; i < 10; i++) {
						window.draw(ourtext[i]);
					}
					window.display();
					dt = gameclock.getElapsedTime().asSeconds();
					set_text_bar(ourtext, rocket, light, score, totalscore);
					settextbar2(ourtext, rocket2, light2, score2, totalscore2);
				}
			}
			//-------------------------------------------------------------------------------------------------------------------//
			if (ch.counter == 30) levels = 7;




			//LEVEL 2
			//-------------------------------------------------------------------------------------------------------------------//
			if (levels == 7) {
				if (restartWord[1] == false) {
					waveclock[1].restart();
					restartWord[1] = true;
				}

				if (waveclock[1].getElapsedTime().asSeconds() < 3) {
					wave[1].move(0.5, 0);
					gun_movement(gun, gun_r_l);
					gun2_movement(gun2, gun2_r_l);
					draw_basic_object(window, space, bar, bar2);
					window.draw(gun);
					window.draw(gun_r_l);
					window.draw(gun2);
					window.draw(gun2_r_l);
					window.draw(wave[1]);
					window.draw(gift);
					window.draw(bar3);
					window.draw(bar4);
					gift.move(0, 0.5);
					window.draw(giftgreen);
					giftgreen.move(0, 0.5);
					window.display();
					wave[1].setString(" Wave  " + to_string(2));
					wave[1].setScale(1, 1);


				}
				else {
					//gun movement
					gun_movement(gun, gun_r_l);
					gun2_movement(gun2, gun2_r_l);
					//chicken movement
					if (ch.hitwall == 0) {
						green_chicken_movement();
					}
					else if (ch.hitwall == 1) {
						green_chicken_movement();
						if (ch.arrchicken[59].getPosition().x < -5) {
							for (int j = 30; j < 60; j++) {
								ch.xstep[j] = -ch.xstep[j];
								ch.arrchicken[j].move(ch.xstep[j], 0);
							}
						}
					}
					//shooting bullets & collision with gifts
					shooting_gain_gifts(gun, gift, giftgreen, gun_r_l, arrfire, fire, firegreen, shot, giftt);
					shooting_gain_gifts2(gun2, gift, giftgreen, gun2_r_l, arrfire, fire, firegreen, shot, giftt);

					//gun_r_l with chicken

					gun_with_chickens(gun_r_l, gun, explosion1, 30, 60, exp, totalscore);
					gun2_with_chicken(gun2_r_l, gun2, explosion1, 30, 60, exp);

					//gun with chickens
					gun_with_chickens(gun, gun_r_l, explosion1, 30, 60, exp, totalscore);
					gun2_with_chicken(gun2, gun2_r_l, explosion1, 30, 60, exp);

					//gun & egg collision
					gun_with_eggs_rocks(gun, gun_r_l, arregg, explosion1, 30, 60, exp);
					gun2_with_eggs_rocks(gun2, gun2_r_l, arregg, explosion1, 30, 60, exp);

					//gun_r_l & egg collision
					gun_with_eggs_rocks(gun_r_l, gun, arregg, explosion1, 30, 60, exp);
					gun2_with_eggs_rocks(gun2_r_l, gun2, arregg, explosion1, 30, 60, exp);
					//killing chicken
					killing_green_chicken(arrleg, totalscore, b.bulletsv, ch_damdge);
					killing_green_chicken(arrleg, totalscore2, b.bulletsv2, ch_damdge);

					//chicken explosion
					set_damage(arrdamage, damageclock, start2, end2);

					//leg collision
					get_chicken_leg(gun, gun_r_l, arrleg, score, start2, end2, totalscore, rocket, Eating_leg);
					get_chicken_leg(gun2, gun2_r_l, arrleg, score2, start2, end2, totalscore2, rocket2, Eating_leg);

					//leg-ground
					leg_with_ground(arrleg, ground, legclock, 30, 60);

					//health

					//random
					gift_random(giftclock, gift, 10);
					gift_random(greengiftclock, giftgreen, 15);
					egg_random(eggclock, arregg, eggrandom, ch.arrchicken, 30, 30, egg_fall);

					egg_with_ground(arregg, ground, arrcrashed_egg, crashedclock, 30, 60, cracked_egg);


					//DRAWING OBJECTS
					window.clear();
					window.draw(space);
					window.draw(giftgreen);
					window.draw(gift);
					for (int i = 30; i < 60; i++) {
						window.draw(arrdamage[i]);
						window.draw(arregg[i]);
						arregg[i].move(0, 0.5);
						window.draw(arrleg[i]);
						window.draw(ch.arrchicken[i]);
						ch.arrchicken[i].move(ch.xstep[i], 0);
						window.draw(arrcrashed_egg[i]);
					}
					for (int i = 0; i < b.bulletsv.size(); i++) {
						window.draw(b.bulletsv[i]);
					}
					for (int i = 0; i < b.bulletsv2.size(); i++) {
						window.draw(b.bulletsv2[i]);
					}
					window.draw(ground);
					window.draw(explosion1);
					window.draw(gun);
					window.draw(gun_r_l);
					window.draw(gun2);
					window.draw(gun2_r_l);
					window.draw(bar);
					window.draw(bar2);
					window.draw(bar3);
					window.draw(bar4);
					for (int i = 0; i < 10; i++) {
						window.draw(ourtext[i]);
					}
					window.display();
					dt = gameclock.getElapsedTime().asSeconds();
					set_text_bar(ourtext, rocket, light, score, totalscore);
					settextbar2(ourtext, rocket2, light2, score2, totalscore2);
				}
			}
			//-------------------------------------------------------------------------------------------------------------------//
			if (ch.counter == 60) levels = 8;


			//LEVEL 3
			//-------------------------------------------------------------------------------------------------------------------//


			if (levels == 8) {
				if (restartWord[2] == false) {
					waveclock[2].restart();
					restartWord[2] = true;
				}
				if (waveclock[2].getElapsedTime().asSeconds() < 3) {
					wave[2].move(0.5, 0);
					gun_movement(gun, gun_r_l);
					gun2_movement(gun2, gun2_r_l);
					draw_basic_object(window, space, bar, bar2);
					window.draw(gun);
					window.draw(gun_r_l);
					window.draw(gun2);
					window.draw(gun2_r_l);
					window.draw(bar3);
					window.draw(bar4);
					window.draw(wave[2]);
					window.display();
					wave[2].setString(" Wave  " + to_string(3));
					wave[2].setScale(1, 1);
				}
				else {
					//MOVEMENT
					gun_movement(gun, gun_r_l);
					gun2_movement(gun2, gun2_r_l);
					// shooting bullets & collision with gifts
					shooting_gain_gifts2(gun2, gift, giftgreen, gun2_r_l, arrfire, fire, firegreen, shot, giftt);
					shooting_gain_gifts(gun, gift, giftgreen, gun_r_l, arrfire, fire, firegreen, shot, giftt);
					//bullets with rocks 
					smash_rocks(arrrocks1, explosion1, fire, b.bulletsv, totalscore, rockexp);
					smash_rocks(arrrocks1, explosion1, fire, b.bulletsv2, totalscore2, rockexp);
					//gun & rocks 
					gun_with_eggs_rocks(gun_r_l, gun, arrrocks1, explosion1, 0, 50, exp);
					gun2_with_eggs_rocks(gun2_r_l, gun2, arrrocks1, explosion1, 0, 50, exp);
					//gun_r_l & rocks
					gun_with_eggs_rocks(gun, gun_r_l, arrrocks1, explosion1, 0, 50, exp);
					gun2_with_eggs_rocks(gun2, gun2_r_l, arrrocks1, explosion1, 0, 50, exp);
					//falling rocks
					rock_random(rockclock, arrrocks1, stop);
					gameoverr(gameover, totalscore);



					// DRAWING OBJECTS
					window.clear();
					window.draw(space);
					for (int i = 0; i < b.bulletsv.size(); i++) {
						window.draw(b.bulletsv[i]);
					}
					for (int i = 0; i < b.bulletsv2.size(); i++) {
						window.draw(b.bulletsv2[i]);
					}
					for (int j = 0; j < 50; j++) {
						window.draw(arrrocks1[j]);
						arrrocks1[j].move(0.2, 0.2);
						arrrocks1[j].rotate(0.05);
					}
					window.draw(gun);
					window.draw(gun_r_l);
					window.draw(gun2);
					window.draw(gun2_r_l);
					window.draw(bar);
					window.draw(bar2);
					window.draw(bar3);
					window.draw(bar4);
					window.draw(explosion1);
					for (int i = 0; i < 10; i++) {
						window.draw(ourtext[i]);
					}
					window.draw(gameover);
					window.display();
					set_text_bar(ourtext, rocket, light, score, totalscore);
					settextbar2(ourtext, rocket2, light2, score2, totalscore2);

				}
			}
			//-------------------------------------------------------------------------------------------------------------------//
			if (r.rocks_counter == 10) { levels = 9;  stop = true; break; }

			//-------------------------------------------------------------------------------------------------------------------//
		}
		if (paused) {
			if (Keyboard::isKeyPressed(Keyboard::R)) {
				paused = false;

			}

			pausefont.setString("resume");

			int vol = volumee / 10;
			window.clear();
			//window.draw(playbutton);
			window.draw(space);
			window.draw(plogo);
			window.draw(button3);
			window.draw(pausefont);
			window.draw(v[vol]);
			window.display();
			dt = gameclock.getElapsedTime().asSeconds();
		}
	}



	while (window.isOpen()) {
		gameclock.restart();
		while (window.pollEvent(event)) {
			if (event.type == Event::Closed) {
				window.close();
			}
			if (event.type == Event::KeyPressed) {

				if (event.key.code == Keyboard::P) {
					if (paused)
						paused = false;
					if (!paused)
						paused = true;

				}
				if (event.key.code == Keyboard::H) {
					if (volumee + 10 <= 90) {
						volumee += 10;

					}
				}
				if (event.key.code == Keyboard::L) {
					if (volumee - 10 >= 0) {
						volumee -= 10;

					}

				}

			}
			ourSound.setVolume(volumee);
		}
		if (!paused) {
			ourSound.play();
			ourSound.setVolume(volumee);


			//LEVEL 4
			//-------------------------------------------------------------------------------------------------------------------//
			if (levels == 9) {
				if (restartWord[3] == false) {
					waveclock[3].restart();
					restartWord[3] = true;
				}
				if (waveclock[3].getElapsedTime().asSeconds() < 3) {
					wave[3].move(0.5, 0);
					gun_movement(gun, gun_r_l);
					gun2_movement(gun2, gun2_r_l);
					draw_basic_object(window, space, bar, bar2);
					window.draw(gun);
					window.draw(gun_r_l);
					window.draw(gun2);
					window.draw(gun2_r_l);
					window.draw(bar3);
					window.draw(bar4);
					window.draw(wave[3]);
					window.display();
					wave[3].setString(" Wave  " + to_string(4));
					wave[3].setScale(1, 1);
				}

				else {
					//MOVEMENT
					gun_movement(gun, gun_r_l);
					gun2_movement(gun2, gun2_r_l);
					boss_movement(boss.chickenboss, delayboss);

					//COLLISIONS
					//shooting
					shooting_gain_gifts(gun, gift, giftgreen, gun_r_l, arrfire, fire, firegreen, shot, giftt);
					shooting_gain_gifts2(gun2, gift, giftgreen, gun2_r_l, arrfire, fire, firegreen, shot, giftt);
					//gun & egg collision
					gun_with_egg(gun_r_l, gun, explosion1, exp);
					gun2_with_egg(gun2_r_l, gun2, explosion1, exp);
					//gun_r_l & egg collision
					gun_with_egg(gun, gun_r_l, explosion1, exp);
					gun2_with_egg(gun2, gun2_r_l, explosion1, exp);
					//gun with chickens
					gun_with_chickenboss(gun_r_l, gun, explosion1, exp);
					gun2_with_chickenboss(gun2_r_l, gun2, explosion1, exp, totalscore2);
					//gun_r_l with chickens
					gun_with_chickenboss(gun, gun_r_l, explosion1, exp);
					gun2_with_chickenboss(gun2, gun2_r_l, explosion1, exp, totalscore2);
					//chicken boss collision
					bullet_chickenboss(gun, gun_r_l, explosion1, b.bulletsv, totalscore, ch_damdge);
					bullet_chickenboss(gun2, gun2_r_l, explosion1, b.bulletsv2, totalscore2, ch_damdge);
					//egg-ground
					egg_with_ground(arregg, ground, arrcrashed_egg, crashedclock, 0, 30, cracked_egg);
					//falling eggs
					egg_random_boss(eggclock, egg_fall);
					gameoverr(gameover, totalscore);
					game_winning(gun, gun_r_l, gun2, gun2_r_l, strings_clock, arrpurple_string, arrblue_string, string__random, win, totalscore, totalscore2);



					//DRAWING OBJECTS
					window.clear();
					window.draw(space);
					for (int i = 0; i < 30; i++) {
						window.draw(arrcrashed_egg[i]);
					}
					for (int i = 0; i < b.bulletsv.size(); i++) {
						window.draw(b.bulletsv[i]);
					}
					for (int i = 0; i < b.bulletsv2.size(); i++) {
						window.draw(b.bulletsv2[i]);
					}
					window.draw(gun);
					window.draw(gun_r_l);
					window.draw(gun2);
					window.draw(gun2_r_l);
					window.draw(oneegg[0].egg);
					oneegg[0].egg.move(0, 0.5);
					window.draw(boss.chickenboss);
					window.draw(bar);
					window.draw(bar2);
					window.draw(bar3);
					window.draw(bar4);
					window.draw(explosion1);
					window.draw(ground);
					window.draw(gameover);
					window.draw(win);

					for (int i = 0; i < 10; i++) {
						window.draw(ourtext[i]);
					}
					for (int i = 0; i < 100; i++) {
						window.draw(arrpurple_string[i]);
						window.draw(arrblue_string[i]);
						arrpurple_string[i].move(0, 0.5);
						arrblue_string[i].move(0, 0.5);
					}
					window.draw(win);
					window.display();
					dt = gameclock.getElapsedTime().asSeconds();
					set_text_bar(ourtext, rocket, light, score, totalscore);
					settextbar2(ourtext, rocket2, light2, score2, totalscore2);

				}
			}
			//-------------------------------------------------------------------------------------------------------------------//

			//-----------------------------------------------------------------------------------------------------------------/--//
		}
		if (paused) {
			if (Keyboard::isKeyPressed(Keyboard::R)) {
				paused = false;

			}
			pausefont.setString("resume");

			int vol = volumee / 10;
			window.clear();
			//window.draw(playbutton);
			window.draw(space);
			window.draw(plogo);
			window.draw(button3);
			window.draw(pausefont);
			window.draw(v[vol]);
			window.display();
			dt = gameclock.getElapsedTime().asSeconds();
		}
	}


	return 0;
}
