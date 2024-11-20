#include "include/main.h"

int main(int argc, char const *argv[])
{
     lcdbuf = load_bmp_as_argb("image/Snake.bmp");
     Snake_body = load_bmp_as_argb("image/Snake_body.bmp");
     Foot_dr = load_bmp_as_argb("image/Foot.bmp");
     show_mmap(lcdbuf);
     initSnake(1);
     addSnakeNode();
     addSnakeNode();
     addSnakeNode();
     addSnakeNode();
     addSnakeNode();
     drowfood(YELLOW); 
     printf("1");
     pthread_t gameplay_thread , creat_foot_;
     pthread_create(&gameplay_thread, NULL, gameplay, NULL);
     pthread_create(&creat_foot_, NULL, create_foot, NULL);
     show_score(0);
     int x, y;
     while (1)
     {
          touch_wait(&x, &y); 
          if (x >= 690 && x <= 735 && y >= 307 && y < 355 && head->dir != DOWN)
          {
               Newdir = UP;
               printf("UP\n");
          }
          else if (x >= 640 && x < 705 && y >= 355 && y < 405 && head->dir != RIGHT)
          {
               Newdir = LEFT;
               printf("LEFT\n");
          }
          else if (x >= 725 && x < 790 && y >= 355 && y < 405 && head->dir != LEFT)
          {
               Newdir = RIGHT;
               printf("RIGHT\n");
          }
          else if (x >= 694 && x < 735 && y >= 393 && y < 455 && head->dir != UP)
          {
               Newdir = DOWN;
               printf("DOWN\n");
          }
     }
}
