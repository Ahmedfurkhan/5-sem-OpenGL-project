#include<windows.h>
#include<stdio.h>
#include<iostream>
#include<GL/glut.h>
#include<string>
#include<sstream>

//folow this copied code


using namespace std;

float barX = 200, barY = 465, barWidth = 80, barheight = 5;
float ballX = 235, ballY=430, ballWH = 10, ballVelX = 0.3, ballVelY = 0.3;
const int brickAmount = 100;
int score = 0, chances = 3, previousScore = 0, highestScore = 0;
bool flag = true, flag2 = true;

struct bricks{
    float x;
    float y;
    float width;
    float height;
    bool isAlive= true;
};
bricks bricksArray[brickAmount];

void createBricks(){
    float brickX = 41, brickY = 50;
    for(int i=0;i<brickAmount;i++){
        if(brickX > 400){
            brickX = 41;
            brickY += 11;
        }
        bricksArray[i].x = brickX;
        bricksArray[i].y = brickY;
        bricksArray[i].width = 38.66;
        bricksArray[i].height = 10;
        brickX += 39.66;
    }
    glColor3ub(0,0,255);
    glBegin(GL_QUADS);
    for(int i=0;i<brickAmount;i++){
        if(bricksArray[i].isAlive == true){
            glVertex2f(bricksArray[i].x, bricksArray[i].y);
            glVertex2f(bricksArray[i].x + bricksArray[i].width, bricksArray[i].y);
            glVertex2f(bricksArray[i].x + bricksArray[i].width, bricksArray[i].y + bricksArray[i].height);
            glVertex2f(bricksArray[i].x, bricksArray[i].y + bricksArray[i].height);
        }
    }
    glEnd();
}

void print(int a){
    glRasterPos2f(490, 40);
    stringstream ss;
    ss << a;
    string s = "Score: "+ss.str();
    int len = s.length();
    for(int i = 0; i < len; i++){
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, s[i]);
    }
    glRasterPos2f(490, 70);
    stringstream ss2;
    ss2 << chances;
    string chance = "Chances left: "+ss2.str();
    for(int i = 0; i < chance.length(); i++){
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, chance[i]);
    }
    glRasterPos2f(490, 100);
    stringstream ss3;
    ss3 << previousScore;
    string prevScore = "Previous score: "+ss3.str();
    for(int i = 0; i < prevScore.length(); i++){
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, prevScore[i]);
    }
    glRasterPos2f(490, 130);
    stringstream ss4;
    ss4 << highestScore;
    string highScore = "Highest score: "+ss4.str();
    for(int i = 0; i < highScore.length(); i++){
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, highScore[i]);
    }
/*    string
    for(int i = 0; i < highScore.length(); i++){
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, highScore[i]);
    }*/
}

void message(bool a){
    if(a == false){
        glRasterPos2f(20, 400);
        stringstream ss;
        ss << previousScore;
        string s = "Game over. Your score: "+ss.str()+". Click to start new game.";
        int len = s.length();
        for(int i = 0; i < len; i++){
            glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, s[i]);
        }
    }
}

void completeMessage(bool a){
    if(a == false){
        glRasterPos2f(20, 400);
        stringstream ss;
        ss << score;
        string s = "STAGE COMPLETE. Your score: "+ss.str()+". Click to start new game.";
        int len = s.length();
        for(int i = 0; i < len; i++){
            glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, s[i]);
        }
    }
}

void myDisplay(void){
    glClear (GL_COLOR_BUFFER_BIT);
    glColor3f (0.0, 0.0, 0.0);
    //Bar
    glBegin(GL_QUADS);
    glColor3ub(255, 204, 102);
    glVertex2f(barX, barY);
    glVertex2f(barX+barWidth, barY);
    glVertex2f(barX+barWidth, barY+barheight);
    glVertex2f(barX, barY+barheight);
    glEnd();
    //Ball
    glBegin(GL_QUADS);
    glColor3ub(255, 0, 0);
    glVertex2f(ballX, ballY);
    glVertex2f(ballX+ballWH, ballY);
    glVertex2f(ballX+ballWH, ballY+ballWH);
    glVertex2f(ballX, ballY+ballWH);
    glEnd();

    //sidebar
    glBegin(GL_QUADS);
    glColor3ub(0, 0, 0);
    glVertex2f(480, 0);
    glVertex2f(480, 480);
    glVertex2f(485, 480);
    glVertex2f(485, 0);
    glEnd();

    print(score);
    createBricks();
    message(flag);
    completeMessage(flag2);

    glutSwapBuffers();
}

void myInit (void){
    glClearColor(1.0, 1.0, 1.0, 0.0);
    glColor3f(0.0f, 0.0f, 0.0f);
    glViewport(0, 0, 760, 480);
    glPointSize(4.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0.0, 760.0, 480.0, 0.0);
}

bool checkCollision(float aX, float aY, float aW, float aH, float bX, float bY, float bW, float bH){
    if ( aY+aH < bY )
        return false;
    else if ( aY > bY+bH )
        return false;
    else if ( aX+aW < bX )
        return false;
    else if ( aX > bX+bW )
        return false;
    else
        return true;
}

void moveBall(){
    if(score >= 300){
        ballVelX = 0.5;
        ballVelY = 0.5;
    }
    if(score >= 1000){
        barX = 200;
        barY = 465;
        ballX = 235;
        ballY = 430;
        ballVelX = 0;
        ballVelY = 0;
        float brickX = 2, brickY = 2;
        for(int i=0;i<brickAmount;i++){
            if(brickX > 450){
                brickX = 2;
                brickY += 11;
            }
            bricksArray[i].x = brickX;
            bricksArray[i].y = brickY;
            bricksArray[i].width = 38.66;
            bricksArray[i].height = 10;
            bricksArray[i].isAlive = true;
            brickX += 39.66;
        }
        previousScore = score;
        if(highestScore < score){
            highestScore = score;
        }
        chances = 3;
        score = 0;
        flag2 = false;
        Sleep(3000);
        completeMessage(flag2);
    }
    else{
        ballX += ballVelX;
        for (int i=0; i<brickAmount; i++){
            if(bricksArray[i].isAlive == true){
                if(checkCollision(ballX, ballY, ballWH, ballWH, bricksArray[i].x, bricksArray[i].y, bricksArray[i].width, bricksArray[i].height) == true){
                    ballVelX = -ballVelX;
                    bricksArray[i].isAlive = false;
                    score += 10;
                    break;
                }
            }
        }
        ballY -= ballVelY;
        for (int i=0; i<brickAmount; i++){
            if(bricksArray[i].isAlive == true){
                if(checkCollision(ballX, ballY, ballWH, ballWH, bricksArray[i].x, bricksArray[i].y, bricksArray[i].width, bricksArray[i].height) == true){
                    ballVelY = -ballVelY;
                    bricksArray[i].isAlive = false;
                    score += 10;
                    break;
                }
            }
        }
        if(ballX < 0){
            ballVelX = -ballVelX;
        }
        else if(ballX+ballWH > 480){
            ballVelX = -ballVelX;
        }
        if(ballY < 0){
            ballVelY = -ballVelY;
        }
        else if(ballY+ballWH > 480){
            if(chances <= 1){
                barX = 200;
                barY = 465;
                ballX = 235;
                ballY = 430;
                ballVelX = 0;
                ballVelY = 0;
                float brickX = 2, brickY = 2;
                for(int i=0;i<brickAmount;i++){
                    if(brickX > 450){
                        brickX = 2;
                        brickY += 11;
                    }
                    bricksArray[i].x = brickX;
                    bricksArray[i].y = brickY;
                    bricksArray[i].width = 38.66;
                    bricksArray[i].height = 10;
                    bricksArray[i].isAlive = true;
                    brickX += 39.66;
                }
                previousScore = score;
                if(highestScore < score){
                    highestScore = score;
                }
                chances = 3;
                score = 0;
                flag = false;
                Sleep(3000);
                message(flag);
            }
            else{
                chances--;
                ballX = 235;
                ballY=430;
                if(ballVelY < 0){
                    ballVelY = -ballVelY;
                }
                Sleep(3000);
            }
        }
        if(checkCollision(ballX, ballY, ballWH, ballWH, barX, barY, barWidth, barheight) == true){
            ballVelY = -ballVelY;
        }
    }
    glutPostRedisplay();
}

void keyboard(int key, int x, int y){
    switch(key){
        case GLUT_KEY_LEFT:
            barX -= 10;
            if(barX < 0){
                barX = 0;
            }
            glutPostRedisplay();
            break;
        case GLUT_KEY_RIGHT:
            barX += 10;
            if(barX+barWidth > 480){
                barX = 480-barWidth;
            }
            glutPostRedisplay();
            break;
        default:
            break;
    }
}

void mouse(int button,int state,int x,int y){
    switch(button){
        case GLUT_LEFT_BUTTON:
            if(state==GLUT_DOWN){
                flag = true;
                if(ballVelX <= 0 && ballVelY <= 0){
                    ballVelX = 0.3;
                    ballVelY = 0.3;
                }
                glutIdleFunc(moveBall);
            }
            break;
        default:
            break;
    }
}

// Reading part

int main(int argc, char** argv){
glutInit(&argc, argv);
glutInitDisplayMode(GLUT_DOUBLE|GLUT_RGB);
glutInitWindowSize(760,480);
glutInitWindowPosition(100,150);
glutCreateWindow("Brick Breaker By Tanvir Hossen Bappy");
glutDisplayFunc(myDisplay);
glutSpecialFunc(keyboard);
glutMouseFunc(mouse);
myInit();
glutMainLoop();
}
