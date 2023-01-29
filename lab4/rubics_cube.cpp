#include <fstream>
#include <GLUT/glut.h> 
#include <iostream>
#include <vector>
#include <thread>
#include <unistd.h>
#include <time.h>
#include "exeption.h"

struct timespec tw = {0,500000000};
struct timespec tr;

using namespace std;

enum color {black, white, green, blue, yellow, red, orange};
static vector<char> c_color{'B', 'W', 'G', 'B', 'Y', 'R', 'O'};
static vector<std::vector<double>> rgb_color{{0, 0, 0}, {1, 1, 1}, {0, 1, 0}, {0, 0, 1}, {1, 1, 0}, {1, 0, 0}, {1, 0.5, 0}};

color char_to_color(const char &c) {
    if (c == 'B') {
        return blue;
    } else if (c == 'W') {
        return white;
    } else if (c == 'G') {
        return green;
    } else if (c == 'Y') {
        return yellow;
    } else if (c == 'R') {
        return red;
    } else {
        return orange;
    }
}

class rube_cube {
    private:
        class cube {
            private:
                color up_ = black;
                color down_ = black;
                color right_ = black;
                color left_ = black;
                color front_ = black;
                color back_ = black;
            public: 
                explicit cube(const color &up, const color &down, const color &left, const color &right, const color &front, const color &back) :
                    up_(up), 
                    down_(down), 
                    right_(right), 
                    left_(left), 
                    front_(front), 
                    back_(back) 
                {}

                cube(const cube &c): 
                    up_(c.up_), 
                    down_(c.down_), 
                    right_(c.right_), 
                    left_(c.left_), 
                    front_(c.front_), 
                    back_(c.back_)
                {}

                cube &operator=(const cube &c) {
                    if (this != &c) {
                        up_ = c.up_;
                        down_ = c.down_;
                        right_ = c.right_;
                        left_ = c.left_;
                        front_ = c.front_;
                        back_ = c.back_;
                    }
                    return *this;
                }

                color get_up() const { return up_; }
                color get_down() const { return down_; }
                color get_left() const { return left_; }
                color get_right() const { return right_; }
                color get_front() const { return front_; }
                color get_back() const { return back_; }
                void set_up(const color &c) { up_ = c; }
                void set_down(const color &c) { down_ = c; }
                void set_left(const color &c) { left_ = c; }
                void set_right(const color &c) { right_ = c; }
                void set_front(const color &c) { front_ = c; }
                void set_back(const color &c) { back_ = c; }
                cube() = default;

                void draw(double x, double y, double z) const {
                    glPushMatrix();
		            glTranslated(x, y, z);
                    glPushMatrix();
                    glBegin(GL_QUADS);
            
                    glColor3f(rgb_color[get_left()][0], rgb_color[get_left()][1], rgb_color[get_left()][2]);
                    glNormal3f(0, 0, 1);
                    glVertex3f(3.8, 3.8, 3.8);          
                    glVertex3f(0, 3.8, 3.8);          
                    glVertex3f(0, 0, 3.8);          
                    glVertex3f(3.8, 0, 3.8);      

                    glColor3f(rgb_color[get_right()][0], rgb_color[get_right()][1], rgb_color[get_right()][2]);
                    glNormal3f(0, 0, -1);
                    glVertex3f(3.8, 0, 0);
                    glVertex3f(0, 0, 0);   
                    glVertex3f(0, 3.8, 0);  
                    glVertex3f(3.8, 3.8, 0);

                    glColor3f(rgb_color[get_back()][0], rgb_color[get_back()][1], rgb_color[get_back()][2]);
                    glNormal3f(0, -1, 0);
                    glVertex3f(3.8, 0, 3.8);
                    glVertex3f(0, 0, 3.8);   
                    glVertex3f(0, 0, 0);      
                    glVertex3f(3.8, 0, 0); 
                    
                    glColor3f(rgb_color[get_front()][0], rgb_color[get_front()][1], rgb_color[get_front()][2]);
                    glNormal3f(0, 1, 0);
                    glVertex3f(3.8, 3.8, 0);   
                    glVertex3f(0, 3.8, 0);      
                    glVertex3f(0, 3.8, 3.8);   
                    glVertex3f(3.8, 3.8, 3.8);

                    glColor3f(rgb_color[get_up()][0], rgb_color[get_up()][1], rgb_color[get_up()][2]);
                    glNormal3f(-1, 0, 0);
                    glVertex3f(0, 3.8, 3.8);   
                    glVertex3f(0, 3.8, 0);      
                    glVertex3f(0, 0, 0);         
                    glVertex3f(0, 0, 3.8);      

                    glColor3f(rgb_color[get_down()][0], rgb_color[get_down()][1], rgb_color[get_down()][2]);
                    glNormal3f(1, 0, 0);
                    glVertex3f(3.8, 3.8, 0);
                    glVertex3f(3.8, 3.8, 3.8);
                    glVertex3f(3.8, 0, 3.8);   
                    glVertex3f(3.8, 0, 0);      
            
                    glEnd();
                    glPopMatrix();
                    glPopMatrix();
                }
        };

        void small_Xrotate(bool side, int k) {
            if (side) {
                for(int i = 0; i < 3; i++) {
                    for(int j = 0; j < 3; j++) {
                        color tmp = cubes[i][j][k].get_up();
                        cubes[i][j][k].set_up(cubes[i][j][k].get_front());
                        cubes[i][j][k].set_front(cubes[i][j][k].get_down());
                        cubes[i][j][k].set_down(cubes[i][j][k].get_back());
                        cubes[i][j][k].set_back(tmp);
                    }
                }
            } else {
                for(int i = 0; i < 3; i++) {
                    for(int j = 0; j < 3; j++) {
                        color tmp = cubes[i][j][k].get_up();
                        cubes[i][j][k].set_up(cubes[i][j][k].get_back());
                        cubes[i][j][k].set_back(cubes[i][j][k].get_down());
                        cubes[i][j][k].set_down(cubes[i][j][k].get_front());
                        cubes[i][j][k].set_front(tmp);
                    }
                }
                
            }
        }

        void small_Zrotate(bool side, int k) {
            if (side) {
                for(int i = 0; i < 3; i++) {
                    for(int j = 0; j < 3; j++) {
                        color tmp = cubes[i][k][j].get_up();
                        cubes[i][k][j].set_up(cubes[i][k][j].get_left());
                        cubes[i][k][j].set_left(cubes[i][k][j].get_down());
                        cubes[i][k][j].set_down(cubes[i][k][j].get_right());
                        cubes[i][k][j].set_right(tmp);
                    }
                }
            } else {
                for(int i = 0; i < 3; i++) {
                    for(int j = 0; j < 3; j++) {
                        color tmp = cubes[i][k][j].get_up();
                        cubes[i][k][j].set_up(cubes[i][k][j].get_right());
                        cubes[i][k][j].set_right(cubes[i][k][j].get_down());
                        cubes[i][k][j].set_down(cubes[i][k][j].get_left());
                        cubes[i][k][j].set_left(tmp);
                    }
                }
            }
        }

        void small_Yrotate(bool side, int k) {
            if (side) {
                for(int i = 0; i < 3; i++) {
                    for(int j = 0; j < 3; j++) {
                        color tmp = cubes[k][i][j].get_back();
                        cubes[k][i][j].set_back(cubes[k][i][j].get_left());
                        cubes[k][i][j].set_left(cubes[k][i][j].get_front());
                        cubes[k][i][j].set_front(cubes[k][i][j].get_right());
                        cubes[k][i][j].set_right(tmp);
                    }
                }
            } else {
                for(int i = 0; i < 3; i++) {
                    for(int j = 0; j < 3; j++) {
                        color tmp = cubes[k][i][j].get_back();
                        cubes[k][i][j].set_back(cubes[k][i][j].get_right());
                        cubes[k][i][j].set_right(cubes[k][i][j].get_front());
                        cubes[k][i][j].set_front(cubes[k][i][j].get_left());
                        cubes[k][i][j].set_left(tmp);
                    }
                }
            }
        }

        vector<vector<vector<cube>>> cubes;
        bool first_step_ready() const {
            return ((cubes[2][2][1].get_down() == down_center_color()) && (cubes[2][0][1].get_down() == down_center_color()) && (cubes[2][1][0].get_down() == down_center_color()) && (cubes[2][1][2].get_down() == down_center_color()) &&
                    (cubes[2][2][1].get_front() == front_center_color()) &&
                    (cubes[2][0][1].get_back() == back_center_color()) &&
                    (cubes[2][1][0].get_right() == right_center_color()) &&
                    (cubes[2][1][2].get_left() == left_center_color()));
        }

        bool second_step_ready() const {
            return (first_step_ready() && 
                    (cubes[2][2][0].get_right() == right_center_color()) && (cubes[2][2][0].get_front() == front_center_color()) &&
                    (cubes[2][2][2].get_left() == left_center_color()) && (cubes[2][2][0].get_front() == front_center_color()) &&
                    (cubes[2][0][0].get_right() == right_center_color()) && (cubes[2][0][0].get_back() == back_center_color()) &&
                    (cubes[2][0][2].get_left() == left_center_color()) && (cubes[2][0][2].get_back() == back_center_color()));
        }

        bool third_step_ready() const {
            return (second_step_ready() && 
                    (cubes[1][2][0].get_right() == right_center_color()) && (cubes[1][2][0].get_front() == front_center_color()) &&
                    (cubes[1][2][2].get_left() == left_center_color()) && (cubes[1][2][0].get_front() == front_center_color()) &&
                    (cubes[1][0][0].get_right() == right_center_color()) && (cubes[1][0][0].get_back() == back_center_color()) &&
                    (cubes[1][0][2].get_left() == left_center_color()) && (cubes[1][0][2].get_back() == back_center_color()));
        }

        bool fourth_step_ready() const {
            return (third_step_ready() && (cubes[0][2][1].get_up() == up_center_color()) && (cubes[0][0][1].get_up() == up_center_color()) && (cubes[0][1][0].get_up() == up_center_color()) && (cubes[0][1][2].get_up() == up_center_color()));
        }

        bool fifth_step_ready() const {
            return ((cubes[0][2][1].get_front() == front_center_color()) &&
                    (cubes[0][0][1].get_back() == back_center_color()) &&
                    (cubes[0][1][0].get_right() == right_center_color()) &&
                    (cubes[0][1][2].get_left() == left_center_color()) &&
                    fourth_step_ready());
        }

        bool sixth_step_ready() const {
            return (fifth_step_ready() && 
                    ((cubes[0][2][0].get_right() == right_center_color()) || (cubes[0][2][0].get_right() == front_center_color()) || (cubes[0][2][0].get_right() == up_center_color())) && 
                    ((cubes[0][2][0].get_front() == right_center_color()) || (cubes[0][2][0].get_front() == front_center_color()) || (cubes[0][2][0].get_front() == up_center_color())) && 
                    ((cubes[0][2][0].get_up() == right_center_color()) || (cubes[0][2][0].get_up() == front_center_color()) || (cubes[0][2][0].get_up() == up_center_color())) && 
                    ((cubes[0][2][2].get_left() == left_center_color()) || (cubes[0][2][2].get_left() == front_center_color()) || (cubes[0][2][2].get_left() == up_center_color())) && 
                    ((cubes[0][2][2].get_front() == left_center_color()) || (cubes[0][2][2].get_front() == front_center_color()) || (cubes[0][2][2].get_front() == up_center_color())) && 
                    ((cubes[0][2][2].get_up() == left_center_color()) || (cubes[0][2][2].get_up() == front_center_color()) || (cubes[0][2][2].get_up() == up_center_color())) && 
                    ((cubes[0][0][0].get_right() == right_center_color()) || (cubes[0][0][0].get_right() == back_center_color()) || (cubes[0][0][0].get_right() == up_center_color())) && 
                    ((cubes[0][0][0].get_back() == right_center_color()) || (cubes[0][0][0].get_back() == back_center_color()) || (cubes[0][0][0].get_back() == up_center_color())) && 
                    ((cubes[0][0][0].get_up() == right_center_color()) || (cubes[0][0][0].get_up() == back_center_color()) || (cubes[0][0][0].get_up() == up_center_color())) && 
                    ((cubes[0][0][2].get_left() == left_center_color()) || (cubes[0][0][2].get_left() == back_center_color()) || (cubes[0][0][2].get_left() == up_center_color())) && 
                    ((cubes[0][0][2].get_back() == left_center_color()) || (cubes[0][0][2].get_back() == back_center_color()) || (cubes[0][0][2].get_back() == up_center_color())) && 
                    ((cubes[0][0][2].get_up() == left_center_color()) || (cubes[0][0][2].get_up() == back_center_color()) || (cubes[0][0][2].get_up() == up_center_color())));
        }

    public:
        rube_cube() {
            cubes.resize(3, vector<vector<cube>>(3,vector<cube>(3)));
        }

        rube_cube(const rube_cube &rb) : cubes(rb.cubes) {}

        rube_cube &operator=(const rube_cube &rb) {
            if (this != &rb) {
                cubes = rb.cubes;
            }
            return *this;
        }

        void find_solution() {
            first_step();
            second_step();
            third_step();
            fourth_step();
            fifth_step();
            sixth_step();
            seventh_step();
        }

        void fill_rube_cube() {
            for(int i = 0; i < 3; i++) {
                for(int j = 0; j < 3; j++) {
                    for(int k = 0; k < 3; k++) {
                        if (i == 0) {
                            cubes[i][j][k].set_up(white);
                        } else if (i == 2) {
                            cubes[i][j][k].set_down(orange);
                        }
                        if (j == 0) {
                            cubes[i][j][k].set_back(red);
                        } else if (j == 2) {
                            cubes[i][j][k].set_front(blue);
                        }
                        if (k == 0) {
                            cubes[i][j][k].set_right(green);
                        } else if (k == 2) {
                            cubes[i][j][k].set_left(yellow);
                        }
                    }
                }
            }
        }

        color front_center_color() const { return cubes[1][2][1].get_front(); }
        color back_center_color() const { return cubes[1][0][1].get_back(); }
        color right_center_color() const { return cubes[1][1][0].get_right(); }
        color left_center_color() const { return cubes[1][1][2].get_left(); }
        color up_center_color() const { return cubes[0][1][1].get_up(); }
        color down_center_color() const { return cubes[2][1][1].get_down(); }

        void draw_cube() {
            for(int i = 0; i < 3; i++)
                for(int j = 0; j < 3; j++)
                    for(int k = 0; k < 3; k++)
                            cubes[i][j][k].draw(4 * i, 4 * j, 4 * k);
        }

        void print_cube(const bool &console) const {
            string svd_cube;
            for (int i = 0; i < 3; i++) {
                svd_cube += "       ";
                for (int j = 2; j >= 0; j--) {
                    svd_cube += c_color[cubes[0][i][j].get_up()];
                    svd_cube += ' ';
                }
                svd_cube += "\n";
            }
            for (int i = 0; i < 3; i++) {
                for (int j = 0; j < 3; j++) {
                    svd_cube += c_color[cubes[i][j][2].get_left()];
                    svd_cube += ' ';
                }
                svd_cube += ' ';
                for (int j = 2; j >= 0; j--) {
                    svd_cube += c_color[cubes[i][2][j].get_front()];
                    svd_cube += ' ';
                }
                svd_cube += ' ';
                for (int j = 2; j >= 0; j--) {
                    svd_cube += c_color[cubes[i][j][0].get_right()];
                    svd_cube += ' ';
                }
                svd_cube += ' ';
                for (int j = 0; j < 3; j++) {
                    svd_cube += c_color[cubes[i][0][j].get_back()];
                    svd_cube += ' ';
                }
                svd_cube += "\n";
            }
            
            for (int i = 2; i >= 0; i--) {
                svd_cube += "       ";
                for (int j = 2; j >= 0 ; j--) {
                    svd_cube += c_color[cubes[2][i][j].get_down()];
                    svd_cube += ' ';
                }
                svd_cube += "\n";
            }

            if (console) {
                cout << svd_cube;
            } else {
                cout << "Введите название файла, в котором необходимо сохранить текущее состояние кубика: \n";
		        string filename;
		        cin >> filename;
		        ofstream fout(filename);
                fout << svd_cube;
                fout.close();
            }
        }

        void read_cube(ifstream &fin) {
            string str;
            int p;
            for(int i = 0; i < 3; i++) {
                getline(fin, str);
                p = 7;
                for (int j = 2; j >= 0; j--) {
                    cubes[0][i][j].set_up(char_to_color(str[p]));
                    p += 2;
                }
            }

            for (int i = 0; i < 3; i++) {
                getline(fin, str);
                p = 0;
                for (int j = 0; j < 3; j++) {
                    cubes[i][j][2].set_left(char_to_color(str[p]));
                    p += 2;
                }
                p++;
                for (int j = 2; j >= 0; j--) {
                    cubes[i][2][j].set_front(char_to_color(str[p]));
                    p += 2;
                }
                p++;
                for (int j = 2; j >= 0; j--) {
                    cubes[i][j][0].set_right(char_to_color(str[p]));
                    p += 2;
                }
                p++;
                for (int j = 0; j < 3; j++) {
                    cubes[i][0][j].set_back(char_to_color(str[p]));
                    p += 2;
                }
            }
            
            for (int i = 2; i >= 0; i--) {
                getline(fin, str);
                p = 7;
                for (int j = 2; j >= 0 ; j--) {
                    cubes[2][i][j].set_down(char_to_color(str[p]));
                    p += 2;
                }
            }
        }

        bool is_gathered() const {
            for (int i = 0; i < 3; i++) {
                for (int j = 0; j < 3; j++) {
                    if (cubes[0][i][j].get_up() != up_center_color()) {
                        return false;
                    }
                }
            }
            for (int i = 0; i < 3; i++) {
                for (int j = 0; j < 3; j++) {
                    if (cubes[2][i][j].get_down() != down_center_color()) {
                        return false;
                    }
                }
            }
            for (int i = 0; i < 3; i++) {
                for (int j = 0; j < 3; j++) {
                    if (cubes[i][j][0].get_right() != right_center_color()) {
                        return false;
                    }
                }
            }
            for (int i = 0; i < 3; i++) {
                for (int j = 0; j < 3; j++) {
                    if (cubes[i][j][2].get_left() != left_center_color()) {
                        return false;
                    }
                }
            }
            for (int i = 0; i < 3; i++) {
                for (int j = 0; j < 3; j++) {
                    if (cubes[i][2][j].get_front() != front_center_color()) {
                        return false;
                    }
                }
            }
            for (int i = 0; i < 3; i++) {
                for (int j = 0; j < 3; j++) {
                    if (cubes[i][0][j].get_back() != back_center_color()) {
                        return false;
                    }
                }
            }
            return true;
        }

        void front_face_rotate(bool side) {
            cube tmp_1 = cubes[0][2][2];
            cube tmp_2 = cubes[0][2][1];
            if (!side) {
                cubes[0][2][2] = cubes[0][2][0];
                cubes[0][2][1] = cubes[1][2][0];
                cubes[0][2][0] = cubes[2][2][0];
                cubes[1][2][0] = cubes[2][2][1];
                cubes[2][2][0] = cubes[2][2][2];
                cubes[2][2][1] = cubes[1][2][2];
                cubes[2][2][2] = tmp_1;
                cubes[1][2][2] = tmp_2;
            } else {
                cubes[0][2][2] = cubes[2][2][2];
                cubes[0][2][1] = cubes[1][2][2];
                cubes[2][2][2] = cubes[2][2][0];
                cubes[1][2][2] = cubes[2][2][1];
                cubes[2][2][0] = cubes[0][2][0];
                cubes[2][2][1] = cubes[1][2][0];
                cubes[0][2][0] = tmp_1;
                cubes[1][2][0] = tmp_2;
            }
            small_Zrotate(side, 2);
        }
        void back_face_rotate(bool side) {
            cube tmp_1 = cubes[0][0][2];
            cube tmp_2 = cubes[0][0][1];
            if (!side) {
                cubes[0][0][2] = cubes[2][0][2];
                cubes[0][0][1] = cubes[1][0][2];
                cubes[2][0][2] = cubes[2][0][0];
                cubes[1][0][2] = cubes[2][0][1];
                cubes[2][0][0] = cubes[0][0][0];
                cubes[2][0][1] = cubes[1][0][0];
                cubes[0][0][0] = tmp_1;
                cubes[1][0][0] = tmp_2;
            } else {
                cubes[0][0][2] = cubes[0][0][0];
                cubes[0][0][1] = cubes[1][0][0];
                cubes[0][0][0] = cubes[2][0][0];
                cubes[1][0][0] = cubes[2][0][1];
                cubes[2][0][0] = cubes[2][0][2];
                cubes[2][0][1] = cubes[1][0][2];
                cubes[2][0][2] = tmp_1;
                cubes[1][0][2] = tmp_2;
                
            }
            small_Zrotate(!side, 0);
        }
        void right_face_rotate(bool side) {
            cube tmp_1 = cubes[0][0][0];
            cube tmp_2 = cubes[0][1][0];
            if (side) {
                cubes[0][0][0] = cubes[0][2][0];
                cubes[0][1][0] = cubes[1][2][0];
                cubes[0][2][0] = cubes[2][2][0];
                cubes[1][2][0] = cubes[2][1][0];
                cubes[2][2][0] = cubes[2][0][0];
                cubes[2][1][0] = cubes[1][0][0];
                cubes[2][0][0] = tmp_1;
                cubes[1][0][0] = tmp_2;
            } else {
                cubes[0][0][0] = cubes[2][0][0];
                cubes[0][1][0] = cubes[1][0][0];
                cubes[2][0][0] = cubes[2][2][0];
                cubes[1][0][0] = cubes[2][1][0];
                cubes[2][2][0] = cubes[0][2][0];
                cubes[2][1][0] = cubes[1][2][0];
                cubes[0][2][0] = tmp_1;
                cubes[1][2][0] = tmp_2;
            }
            small_Xrotate(side, 0);
        }
        void left_face_rotate(bool side) {
            cube tmp_1 = cubes[0][0][2];
            cube tmp_2 = cubes[0][1][2];
            if (side) {
                cubes[0][0][2] = cubes[2][0][2];
                cubes[0][1][2] = cubes[1][0][2];
                cubes[2][0][2] = cubes[2][2][2];
                cubes[1][0][2] = cubes[2][1][2];
                cubes[2][2][2] = cubes[0][2][2];
                cubes[2][1][2] = cubes[1][2][2];
                cubes[0][2][2] = tmp_1;
                cubes[1][2][2] = tmp_2;
            } else {
                cubes[0][0][2] = cubes[0][2][2];
                cubes[0][1][2] = cubes[1][2][2];
                cubes[0][2][2] = cubes[2][2][2];
                cubes[1][2][2] = cubes[2][1][2];
                cubes[2][2][2] = cubes[2][0][2];
                cubes[2][1][2] = cubes[1][0][2];
                cubes[2][0][2] = tmp_1;
                cubes[1][0][2] = tmp_2;
            }
            small_Xrotate(!side, 2);
        }
        void up_face_rotate(bool side) {
            cube tmp_1 = cubes[0][0][2];
            cube tmp_2 = cubes[0][0][1];
            if (!side) {
                cubes[0][0][2] = cubes[0][0][0];
                cubes[0][0][1] = cubes[0][1][0];
                cubes[0][0][0] = cubes[0][2][0];
                cubes[0][1][0] = cubes[0][2][1];
                cubes[0][2][0] = cubes[0][2][2];
                cubes[0][2][1] = cubes[0][1][2];
                cubes[0][2][2] = tmp_1;
                cubes[0][1][2] = tmp_2;
            } else {
                cubes[0][0][2] = cubes[0][2][2];
                cubes[0][0][1] = cubes[0][1][2];
                cubes[0][2][2] = cubes[0][2][0];
                cubes[0][1][2] = cubes[0][2][1];
                cubes[0][2][0] = cubes[0][0][0];
                cubes[0][2][1] = cubes[0][1][0];
                cubes[0][0][0] = tmp_1;
                cubes[0][1][0] = tmp_2;
            }
            small_Yrotate(side, 0);
        }
        void down_face_rotate(bool side) {
            cube tmp_1 = cubes[2][0][2];
            cube tmp_2 = cubes[2][0][1];
            if (!side) {
                cubes[2][0][2] = cubes[2][2][2];
                cubes[2][0][1] = cubes[2][1][2];
                cubes[2][2][2] = cubes[2][2][0];
                cubes[2][1][2] = cubes[2][2][1];
                cubes[2][2][0] = cubes[2][0][0];
                cubes[2][2][1] = cubes[2][1][0];
                cubes[2][0][0] = tmp_1;
                cubes[2][1][0] = tmp_2;
            } else {
                cubes[2][0][2] = cubes[2][0][0];
                cubes[2][0][1] = cubes[2][1][0];
                cubes[2][0][0] = cubes[2][2][0];
                cubes[2][1][0] = cubes[2][2][1];
                cubes[2][2][0] = cubes[2][2][2];
                cubes[2][2][1] = cubes[2][1][2];
                cubes[2][2][2] = tmp_1;
                cubes[2][1][2] = tmp_2;
            }
            small_Yrotate(!side, 2);
        }
        void make_rotations(const std::string &rotations, const bool &out) {
            if (out) {
                cout << rotations;
            }

            int i = 0;
            while (i < rotations.size()) {
                if (rotations[i] == 'U') {
                    if ((i + 1 < rotations.size()) && (rotations[i+1] == '\'')) {
                        up_face_rotate(false);
                        i++;
                    } else {
                        up_face_rotate(true);
                    }
                } else if (rotations[i] == 'D') {
                    if ((i + 1 < rotations.size()) && (rotations[i+1] == '\'')) {
                        down_face_rotate(false);
                        i++;
                    } else {
                        down_face_rotate(true);
                    }
                } else if (rotations[i] == 'R') {
                    if ((i + 1 < rotations.size()) && (rotations[i+1] == '\'')) {
                        right_face_rotate(false);
                        i++;
                    } else {
                        right_face_rotate(true);
                    }
                } else if (rotations[i] == 'L') {
                    if ((i + 1 < rotations.size()) && (rotations[i+1] == '\'')) {
                        left_face_rotate(false);
                        i++;
                    } else {
                        left_face_rotate(true);
                    }
                } else if (rotations[i] == 'F') {
                    if ((i + 1 < rotations.size()) && (rotations[i+1] == '\'')) {
                        front_face_rotate(false);
                        i++;
                    } else {
                        front_face_rotate(true);
                    }
                } else if (rotations[i] == 'B') {
                    if ((i + 1 < rotations.size()) && (rotations[i+1] == '\'')) {
                        back_face_rotate(false);
                        i++;
                    } else {
                        back_face_rotate(true);
                    }
                }
                i++;
            }
            std::cout << rotations;
        }

        void random_rotate() {
            int rotates_count = 1 + rand() % 15;
            for (int i = 0; i < rotates_count; i++) {
                int cur = 1 + rand() % 12;
                if ((cur == 1) || (cur == 2)) {
                    front_face_rotate(cur%2);
                } else if ((cur == 3) || (cur == 4)) {
                    back_face_rotate(cur%2);
                } else if ((cur == 5) || (cur == 6)) {
                    right_face_rotate(cur%2);
                } else if ((cur == 7) || (cur == 8)) {
                    left_face_rotate(cur%2);
                } else if ((cur == 9) || (cur == 10)) {
                    up_face_rotate(cur%2);
                } else {
                    down_face_rotate(cur%2);
                }
            }
        }


        void first_step() {
            int i = 0;
            int count = 0;
            while (i < 80) {
                i++;
                bool conf = false;
                if ((cubes[0][2][1].get_front() == front_center_color()) && (cubes[0][2][1].get_up() == down_center_color())) {
                    make_rotations("F'F'", true);
                    conf = true;
                } else if ((cubes[0][1][0].get_right() == right_center_color()) && (cubes[0][1][0].get_up() == down_center_color())) {
                    make_rotations("R'R'", true);
                    conf = true;
                } else if ((cubes[0][1][2].get_left() == left_center_color()) && (cubes[0][1][2].get_up() == down_center_color())) {
                    make_rotations("L'L'", true);
                    conf = true;
                } else if ((cubes[0][0][1].get_back() == back_center_color()) && (cubes[0][0][1].get_up() == down_center_color())) {
                    make_rotations("B'B'", true);
                    conf = true;
                } else if ((cubes[0][2][1].get_up() == front_center_color()) && (cubes[0][2][1].get_front() == down_center_color())) {
                    make_rotations("U'R'FR", true);
                    conf = true;
                } else if ((cubes[0][1][0].get_up() == right_center_color()) && (cubes[0][1][0].get_right() == down_center_color())) {
                    make_rotations("U'B'RB", true);
                    conf = true;
                } else if ((cubes[0][1][2].get_up() == left_center_color()) && (cubes[0][1][2].get_left() == down_center_color())) {
                    make_rotations("U'F'LF", true);
                    conf = true;
                } else if ((cubes[0][0][1].get_up() == back_center_color()) && (cubes[0][0][1].get_back() == down_center_color())) {
                    make_rotations("U'L'BL", true);
                    conf = true;
                } else if (cubes[1][2][0].get_front() == down_center_color()) {
                    make_rotations("F'U'F", true);
                    conf = true;
                } else if (cubes[1][0][0].get_right() == down_center_color()) {
                    make_rotations("R'U'R", true);
                    conf = true;
                } else if (cubes[1][2][2].get_left() == down_center_color()) {
                    make_rotations("L'U'L", true);
                    conf = true;
                } else if (cubes[1][0][2].get_back() == down_center_color()) {
                    make_rotations("B'U'B", true);
                    conf = true;
                } else if (cubes[1][2][2].get_front() == down_center_color()) {
                    make_rotations("FU'F'", true);
                    conf = true;
                } else if (cubes[1][2][0].get_right() == down_center_color()) {
                    make_rotations("RU'R'", true);
                    conf = true;
                } else if (cubes[1][0][2].get_left() == down_center_color()) {
                    make_rotations("LU'L'", true);
                    conf = true;
                } else if (cubes[1][0][0].get_back() == down_center_color()) {
                    make_rotations("BU'B'", true);
                    conf = true;
                } else if ((cubes[2][2][1].get_front() == down_center_color()) || ((cubes[2][2][1].get_front() != front_center_color()) && (cubes[2][2][1].get_down() == down_center_color()))) {
                    make_rotations("F'F'U'F'F'", true);
                    conf = true;
                } else if ((cubes[2][1][0].get_right() == down_center_color()) || ((cubes[2][1][0].get_right() != right_center_color()) && (cubes[2][1][0].get_down() == down_center_color()))) {
                    make_rotations("R'R'U'R'R'", true);
                    conf = true;
                } else if ((cubes[2][1][2].get_left() == down_center_color()) || ((cubes[2][1][2].get_left() != left_center_color()) && (cubes[2][1][2].get_down() == down_center_color()))) {
                    make_rotations("L'L'U'L'L'", true);
                    conf = true;
                } else if ((cubes[2][0][1].get_back() == down_center_color()) || ((cubes[2][0][1].get_back() != back_center_color()) && (cubes[2][0][1].get_down() == down_center_color()))){
                    make_rotations("B'B'U'B'B'", true);
                    conf = true;
                }
                if (!conf) {
                    up_face_rotate(true);
                    count++;
                    if (count == 4) {
                        return;
                    }
                } else {
                    count = 0;
                }
            }
            if (!first_step_ready()) {
                throw not_valid_object("Cube isn't correct 1");
            }   
        }
        void second_step() {
            if (!first_step_ready()) {
                throw not_valid_object("Cube isn't correct 1");
            }   
            int i = 0;
            int count = 0;
            while (i < 80) {
                i++;
                bool conf = false;
                if (((cubes[0][2][0].get_front() == down_center_color()) && (cubes[0][2][0].get_up() == front_center_color()) && (cubes[0][2][0].get_right() == right_center_color())) || (cubes[2][2][0].get_front() == down_center_color()) || (cubes[2][2][0].get_right() == down_center_color())) {
                    make_rotations("F'U'F", true);
                    conf = true;
                } else if (((cubes[0][2][2].get_left() == down_center_color()) && (cubes[0][2][2].get_front() == front_center_color()) && (cubes[0][2][2].get_up() == left_center_color())) || (cubes[2][2][2].get_left() == down_center_color()) || (cubes[2][2][2].get_front() == down_center_color())) {
                    make_rotations("L'U'L", true);
                    conf = true;
                } else if (((cubes[0][0][0].get_right() == down_center_color()) && (cubes[0][0][0].get_up() == right_center_color()) && (cubes[0][0][0].get_back() == back_center_color())) || (cubes[2][0][0].get_right() == down_center_color()) || (cubes[2][0][0].get_back() == down_center_color())) {
                    make_rotations("R'U'R", true);
                    conf = true;
                } else if (((cubes[0][0][2].get_back() == down_center_color()) && (cubes[0][0][2].get_up() == back_center_color()) && (cubes[0][0][2].get_left() == left_center_color())) || (cubes[2][0][2].get_back() == down_center_color()) || (cubes[2][0][2].get_left() == down_center_color())){
                    make_rotations("B'U'B", true);
                    conf = true;
                } else if ((cubes[0][2][0].get_right() == down_center_color()) && (cubes[0][2][0].get_front() == front_center_color()) && (cubes[0][2][0].get_up() == right_center_color())) {
                    make_rotations("RUR'", true);
                    conf = true;
                } else if ((cubes[0][2][2].get_front() == down_center_color()) && (cubes[0][2][2].get_up() == front_center_color()) && (cubes[0][2][2].get_left() == left_center_color())) {
                    make_rotations("FUF'", true);
                    conf = true;
                } else if ((cubes[0][0][0].get_back() == down_center_color()) && (cubes[0][0][0].get_right() == right_center_color()) && (cubes[0][0][0].get_up() == back_center_color())) {
                    make_rotations("BUB'", true);
                    conf = true;
                } else if ((cubes[0][0][2].get_left() == down_center_color()) && (cubes[0][0][2].get_back() == back_center_color()) && (cubes[0][0][2].get_up() == left_center_color())) {
                    make_rotations("LUL'", true);
                    conf = true;
                } else if ((cubes[0][2][0].get_up() == down_center_color()) && (cubes[0][2][0].get_right() == front_center_color()) && (cubes[0][2][0].get_front() == right_center_color())) {
                    make_rotations("RU'R'U'U'RUR'", true);
                    conf = true;
                } else if ((cubes[0][2][2].get_up() == down_center_color()) && (cubes[0][2][2].get_left() == front_center_color()) && (cubes[0][2][2].get_front() == left_center_color())) {
                    make_rotations("FU'F'U'U'FUF'", true);
                    conf = true;
                } else if ((cubes[0][0][0].get_up() == down_center_color()) && (cubes[0][0][0].get_back() == right_center_color()) && (cubes[0][0][0].get_right() == back_center_color())) {
                    make_rotations("BU'B'U'U'BUB'", true);
                    conf = true;
                } else if ((cubes[0][0][2].get_up() == down_center_color()) && (cubes[0][0][2].get_left() == back_center_color()) && (cubes[0][0][2].get_back() == left_center_color())) {
                    make_rotations("LU'L'U'U'LUL'", true);
                    conf = true;
                } else if ((cubes[2][2][2].get_down() == down_center_color()) && ((cubes[2][2][2].get_left() != left_center_color()) || (cubes[2][2][2].get_front() != front_center_color()))){
                    make_rotations("FU'F'", true);
                    conf = true;
                } else if ((cubes[2][2][0].get_down() == down_center_color()) && ((cubes[2][2][0].get_right() != right_center_color()) || (cubes[2][2][0].get_front() != front_center_color()))){
                    make_rotations("RU'R'", true);
                    conf = true;
                } else if ((cubes[2][0][0].get_down() == down_center_color()) && ((cubes[2][0][0].get_right() != right_center_color()) || (cubes[2][0][0].get_back() != back_center_color()))){
                    make_rotations("BU'B'", true);
                    conf = true;
                } else if ((cubes[2][0][2].get_down() == down_center_color()) && ((cubes[2][0][2].get_left() != left_center_color()) || (cubes[2][0][2].get_back() != back_center_color()))){
                    make_rotations("LU'L'", true);
                    conf = true;
                }
                if (!conf) {
                    up_face_rotate(true);
                    count++;
                    if (count == 4) {
                        return;
                    }
                } else {
                    count = 0;
                }
            }
            if (!second_step_ready()) {
                throw not_valid_object("Cube isn't correct 2");
            }
        }

        void third_step() {
            if (!second_step_ready()) {
                throw not_valid_object("Cube isn't correct 2");
            }
            int i = 0;
            int count = 0;
            while (i < 80) {
                i++;
                bool conf = false;
                if ((cubes[0][2][1].get_front() == front_center_color()) && (cubes[0][2][1].get_up() == left_center_color())) {
                    make_rotations("U'L'ULUFU'F'", true);
                    conf = true;
                } else if ((cubes[0][1][0].get_right() == right_center_color()) && (cubes[0][1][0].get_up() == front_center_color())) {
                    make_rotations("U'F'UFURU'R'", true);
                    conf = true;
                } else if ((cubes[0][0][1].get_back() == back_center_color()) && (cubes[0][0][1].get_up() == right_center_color())) {
                    make_rotations("U'R'URUBU'B'", true);
                    conf = true;
                } else if ((cubes[0][1][2].get_left() == left_center_color()) && (cubes[0][1][2].get_up() == back_center_color())) {
                    make_rotations("U'B'UBULU'L'", true);
                    conf = true;
                } else if ((cubes[0][2][1].get_front() == front_center_color()) && (cubes[0][2][1].get_up() == right_center_color())) {
                    make_rotations("URU'R'U'F'UF", true);
                    conf = true;
                } else if ((cubes[0][1][0].get_right() == right_center_color()) && (cubes[0][1][0].get_up() == back_center_color())) {
                    make_rotations("UBU'B'U'R'UR", true);
                    conf = true;
                } else if ((cubes[0][0][1].get_back() == back_center_color()) && (cubes[0][0][1].get_up() == left_center_color())) {
                    make_rotations("ULU'L'U'B'UB", true);
                    conf = true;
                } else if ((cubes[0][1][2].get_left() == left_center_color()) && (cubes[0][1][2].get_up() == front_center_color())) {
                    make_rotations("UFU'F'U'L'UL", true);
                    conf = true;
                }

                if (!conf) {
                    up_face_rotate(true);
                    count++;
                    if (count == 4) {
                        if ((cubes[1][2][0].get_front() != front_center_color()) || (cubes[1][2][0].get_right() != right_center_color())) {
                            make_rotations("URU'R'U'F'UF", true);
                        } else if ((cubes[1][2][2].get_front() != front_center_color()) || (cubes[1][2][2].get_left() != left_center_color())) {
                            make_rotations("UFU'F'U'L'UL", true);
                        } else if ((cubes[1][0][2].get_back() != back_center_color()) || (cubes[1][0][2].get_left() != left_center_color())) {
                            make_rotations("ULU'L'U'B'UB", true);
                        } else if ((cubes[1][0][0].get_back() != back_center_color()) || (cubes[1][0][0].get_right() != right_center_color())) {
                            make_rotations("UBU'B'U'R'UR", true);
                        } else {
                           return; 
                        }
                    }
                } else {
                    count = 0;
                }
            }
            if (!third_step_ready()) {
                throw not_valid_object("Cube isn't correct 3");
            }
        }
        void fourth_step() {
            if (!third_step_ready()) {
                throw not_valid_object("Cube isn't correct 3");
            }
            if ((cubes[0][0][1].get_up() == up_center_color()) && (cubes[0][1][2].get_up() == up_center_color()) && (cubes[0][1][0].get_right() == up_center_color()) && (cubes[0][2][1].get_front() == up_center_color())) {
                make_rotations("FURU'R'F'", true);
            } else if ((cubes[0][0][1].get_up() == up_center_color()) && (cubes[0][1][2].get_left() == up_center_color()) && (cubes[0][1][0].get_up() == up_center_color()) && (cubes[0][2][1].get_front() == up_center_color())) {
                make_rotations("LUFU'F'L'", true);
            } else if ((cubes[0][0][1].get_back() == up_center_color()) && (cubes[0][1][2].get_up() == up_center_color()) && (cubes[0][1][0].get_right() == up_center_color()) && (cubes[0][2][1].get_up() == up_center_color())) {
                make_rotations("RUBU'B'R'", true);
            } else if ((cubes[0][0][1].get_back() == up_center_color()) && (cubes[0][1][2].get_left() == up_center_color()) && (cubes[0][1][0].get_up() == up_center_color()) && (cubes[0][2][1].get_up() == up_center_color())) {
                make_rotations("BULU'L'B'", true);
            } else if ((cubes[0][0][1].get_back() == up_center_color()) && (cubes[0][1][2].get_up() == up_center_color()) && (cubes[0][1][0].get_up() == up_center_color()) && (cubes[0][2][1].get_front() == up_center_color())) {
                make_rotations("FRUR'U'F'", true);
            } else if ((cubes[0][0][1].get_up() == up_center_color()) && (cubes[0][1][2].get_left() == up_center_color()) && (cubes[0][1][0].get_right() == up_center_color()) && (cubes[0][2][1].get_up() == up_center_color())) {
                make_rotations("RBUB'U'R'", true);
            } else if ((cubes[0][0][1].get_back() == up_center_color()) && (cubes[0][1][2].get_left() == up_center_color()) && (cubes[0][1][0].get_right() == up_center_color()) && (cubes[0][2][1].get_front() == up_center_color())) {
                make_rotations("FURU'R'F'RBUB'U'R'", true);
            }
            if (!fourth_step_ready()) {
                throw not_valid_object("Cube isn't correct 4");
            }
        }

        void fifth_step() {
            if (cubes[0][1][0].get_right() == front_center_color())  {
                make_rotations("UL'U'U'LUL'UL", true);
            } else if (cubes[0][1][2].get_left() == front_center_color())  {
                make_rotations("UB'U'U'BUB'UB", true);
            } else if (cubes[0][0][1].get_back() == front_center_color())  {
                make_rotations("UR'U'U'RUR'URUB'U'U'BUB'UBUR'U'U'RUR'UR", true);
            } 
            if (cubes[0][0][1].get_back() == right_center_color()) {
                make_rotations("UF'U'U'FUF'UF", true);
            } else if (cubes[0][1][2].get_left() == right_center_color()) {
                make_rotations("UB'U'U'BUB'UBUL'U'U'LUL'ULUB'U'U'BUB'UB", true);
            } 
            if (cubes[0][1][2].get_left() == back_center_color()) {
                make_rotations("UR'U'U'RUR'UR", true);
            }
            if (!fifth_step_ready()) {
                throw not_valid_object("Cube isn't correct 5");
            }
        }

        void sixth_step() {
            if (((cubes[0][2][2].get_up() == front_center_color()) && (cubes[0][2][2].get_left() == right_center_color()) && (cubes[0][2][2].get_front() == up_center_color())) ||
               ((cubes[0][2][2].get_up() == front_center_color()) && (cubes[0][2][2].get_left() == up_center_color()) && (cubes[0][2][2].get_front() == right_center_color())) || 
               ((cubes[0][2][2].get_up() == right_center_color()) && (cubes[0][2][2].get_left() == front_center_color()) && (cubes[0][2][2].get_front() == up_center_color())) || 
               ((cubes[0][2][2].get_up() == right_center_color()) && (cubes[0][2][2].get_left() == up_center_color()) && (cubes[0][2][2].get_front() == front_center_color())) ||
               ((cubes[0][2][2].get_up() == up_center_color()) && (cubes[0][2][2].get_left() == front_center_color()) && (cubes[0][2][2].get_front() == right_center_color())) || 
               ((cubes[0][2][2].get_up() == up_center_color()) && (cubes[0][2][2].get_left() == right_center_color()) && (cubes[0][2][2].get_front() == front_center_color()))) {
                make_rotations("F'L'FR'F'LFR", true);
            } 
            if (((cubes[0][0][0].get_up() == front_center_color()) && (cubes[0][0][0].get_right() == right_center_color()) && (cubes[0][0][0].get_back() == up_center_color())) ||
               ((cubes[0][0][0].get_up() == front_center_color()) && (cubes[0][0][0].get_right() == up_center_color()) && (cubes[0][0][0].get_back() == right_center_color())) || 
               ((cubes[0][0][0].get_up() == right_center_color()) && (cubes[0][0][0].get_right() == front_center_color()) && (cubes[0][0][0].get_back() == up_center_color())) || 
               ((cubes[0][0][0].get_up() == right_center_color()) && (cubes[0][0][0].get_right() == up_center_color()) && (cubes[0][0][0].get_back() == front_center_color())) ||
               ((cubes[0][0][0].get_up() == up_center_color()) && (cubes[0][0][0].get_right() == front_center_color()) && (cubes[0][0][0].get_back() == right_center_color())) || 
               ((cubes[0][0][0].get_up() == up_center_color()) && (cubes[0][0][0].get_right() == right_center_color()) && (cubes[0][0][0].get_back() == front_center_color()))) {
                make_rotations("R'F'L'FRF'LF", true);
            } 
            if (((cubes[0][0][2].get_up() == front_center_color()) && (cubes[0][0][2].get_left() == right_center_color()) && (cubes[0][0][2].get_back() == up_center_color())) ||
               ((cubes[0][0][2].get_up() == front_center_color()) && (cubes[0][0][2].get_left() == up_center_color()) && (cubes[0][0][2].get_back() == right_center_color())) || 
               ((cubes[0][0][2].get_up() == right_center_color()) && (cubes[0][0][2].get_left() == front_center_color()) && (cubes[0][0][2].get_back() == up_center_color())) || 
               ((cubes[0][0][2].get_up() == right_center_color()) && (cubes[0][0][2].get_left() == up_center_color()) && (cubes[0][0][2].get_back() == front_center_color())) ||
               ((cubes[0][0][2].get_up() == up_center_color()) && (cubes[0][0][2].get_left() == front_center_color()) && (cubes[0][0][2].get_back() == right_center_color())) || 
               ((cubes[0][0][2].get_up() == up_center_color()) && (cubes[0][0][2].get_left() == right_center_color()) && (cubes[0][0][2].get_back() == front_center_color()))) {
                make_rotations("F'L'B'LFL'BL", true);
            } 
            if (((cubes[0][2][2].get_up() == back_center_color()) && (cubes[0][2][2].get_left() == right_center_color()) && (cubes[0][2][2].get_front() == up_center_color())) ||
               ((cubes[0][2][2].get_up() == back_center_color()) && (cubes[0][2][2].get_left() == up_center_color()) && (cubes[0][2][2].get_front() == right_center_color())) || 
               ((cubes[0][2][2].get_up() == right_center_color()) && (cubes[0][2][2].get_left() == back_center_color()) && (cubes[0][2][2].get_front() == up_center_color())) || 
               ((cubes[0][2][2].get_up() == right_center_color()) && (cubes[0][2][2].get_left() == up_center_color()) && (cubes[0][2][2].get_front() == back_center_color())) ||
               ((cubes[0][2][2].get_up() == up_center_color()) && (cubes[0][2][2].get_left() == back_center_color()) && (cubes[0][2][2].get_front() == right_center_color())) || 
               ((cubes[0][2][2].get_up() == up_center_color()) && (cubes[0][2][2].get_left() == right_center_color()) && (cubes[0][2][2].get_front() == back_center_color()))) {
                make_rotations("B'R'BL'B'RBL", true);
            } 
            if (((cubes[0][0][2].get_up() == back_center_color()) && (cubes[0][0][2].get_left() == right_center_color()) && (cubes[0][0][2].get_back() == up_center_color())) ||
               ((cubes[0][0][2].get_up() == back_center_color()) && (cubes[0][0][2].get_left() == up_center_color()) && (cubes[0][0][2].get_back() == right_center_color())) || 
               ((cubes[0][0][2].get_up() == right_center_color()) && (cubes[0][0][2].get_left() == back_center_color()) && (cubes[0][0][2].get_back() == up_center_color())) || 
               ((cubes[0][0][2].get_up() == right_center_color()) && (cubes[0][0][2].get_left() == up_center_color()) && (cubes[0][0][2].get_back() == back_center_color())) ||
               ((cubes[0][0][2].get_up() == up_center_color()) && (cubes[0][0][2].get_left() == back_center_color()) && (cubes[0][0][2].get_back() == right_center_color())) || 
               ((cubes[0][0][2].get_up() == up_center_color()) && (cubes[0][0][2].get_left() == right_center_color()) && (cubes[0][0][2].get_back() == back_center_color()))) {
                make_rotations("L'B'R'BLB'RB", true);
            }
            if (!sixth_step_ready()) {
                throw not_valid_object("Cube isn't correct 6");
            }
        }
        void seventh_step() {
            int i = 0;
            int count = 0;
            while(i < 80) {
                i++;
                bool conf = false;
                if (cubes[0][2][0].get_right() == up_center_color()) {
                    make_rotations("F'RFR'F'RFR'", true);
                    conf = true;
                } else if (cubes[0][2][0].get_front() == up_center_color()) {
                    make_rotations("RF'R'FRF'R'F", true);
                    conf = true;
                }
                if (!conf) {
                    up_face_rotate(true);
                    count++;
                    if (count == 4) {
                        while (!is_gathered()) {
                            up_face_rotate(true);
                        }
                        return;
                    }
                } else {
                    count = 0;
                }
            }
            throw not_valid_object("Cube isn't correct 7");
        }

        
};