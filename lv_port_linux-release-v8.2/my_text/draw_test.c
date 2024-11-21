#include "../lvgl/lvgl.h"

void Draw_test()
{
    lv_obj_t * main_windows = lv_obj_create(NULL);
    lv_obj_t * btn = lv_btn_create(main_windows);//创建按钮
    lv_obj_set_size(btn,100,100);
    lv_obj_set_align(btn,LV_ALIGN_CENTER); //按钮居中

    lv_obj_t *label = lv_label_create(btn);//给按钮添加标签
    lv_label_set_text(label,"BUTTUN");
    lv_obj_center(label);//设置居中

    // lv_obj_t * img_lqx = lv_img_create(main_windows);
    // lv_img_set_src(img_lqx, "S:/mnt/share/lv_port_linux-release-v8.2/my_text/img/q.jpg");
    // lv_obj_set_pos(img_lqx,0,0);

    // lv_obj_t * huawei = lv_img_create(main_windows);
    // lv_img_set_src(huawei, "S:/mnt/share/lv_port_linux-release-v8.2/my_text/img/huawei.jpg");
    // lv_obj_set_pos(huawei,0,0);
    // lv_obj_set_size(huawei,800,480);

    //加载控件
  
    lv_scr_load(main_windows);
  
}
