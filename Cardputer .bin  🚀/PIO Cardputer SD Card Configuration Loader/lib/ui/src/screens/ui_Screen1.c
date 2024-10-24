// This file was generated by SquareLine Studio
// SquareLine Studio version: SquareLine Studio 1.4.2
// LVGL version: 8.3.6
// Project name: pip card

#include "../ui.h"

void ui_Screen1_screen_init(void)
{
ui_Screen1 = lv_obj_create(NULL);
lv_obj_clear_flag( ui_Screen1, LV_OBJ_FLAG_SCROLLABLE );    /// Flags
lv_obj_set_style_bg_color(ui_Screen1, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT );
lv_obj_set_style_bg_opa(ui_Screen1, 255, LV_PART_MAIN| LV_STATE_DEFAULT);

ui_Tab_main = lv_tabview_create(ui_Screen1, LV_DIR_TOP, 30);
lv_obj_set_width( ui_Tab_main, 240);
lv_obj_set_height( ui_Tab_main, 135);
lv_obj_set_align( ui_Tab_main, LV_ALIGN_CENTER );
lv_obj_clear_flag( ui_Tab_main, LV_OBJ_FLAG_SCROLLABLE );    /// Flags
lv_obj_set_style_bg_color(ui_Tab_main, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT );
lv_obj_set_style_bg_opa(ui_Tab_main, 255, LV_PART_MAIN| LV_STATE_DEFAULT);

lv_obj_set_style_text_color(lv_tabview_get_tab_btns(ui_Tab_main), lv_color_hex(0x00C003),  LV_PART_MAIN | LV_STATE_DEFAULT );
lv_obj_set_style_text_opa(lv_tabview_get_tab_btns(ui_Tab_main), 255,  LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_text_font(lv_tabview_get_tab_btns(ui_Tab_main), &ui_font_J35,  LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_bg_color(lv_tabview_get_tab_btns(ui_Tab_main), lv_color_hex(0xFFFFFF),  LV_PART_MAIN | LV_STATE_DEFAULT );
lv_obj_set_style_bg_opa(lv_tabview_get_tab_btns(ui_Tab_main), 0,  LV_PART_MAIN| LV_STATE_DEFAULT);

lv_obj_set_style_border_color(lv_tabview_get_tab_btns(ui_Tab_main), lv_color_hex(0x00C200),  LV_PART_ITEMS | LV_STATE_DEFAULT );
lv_obj_set_style_border_opa(lv_tabview_get_tab_btns(ui_Tab_main), 255,  LV_PART_ITEMS| LV_STATE_DEFAULT);
lv_obj_set_style_border_width(lv_tabview_get_tab_btns(ui_Tab_main), 2,  LV_PART_ITEMS| LV_STATE_DEFAULT);
lv_obj_set_style_border_side(lv_tabview_get_tab_btns(ui_Tab_main), LV_BORDER_SIDE_BOTTOM,  LV_PART_ITEMS| LV_STATE_DEFAULT);
lv_obj_set_style_text_color(lv_tabview_get_tab_btns(ui_Tab_main), lv_color_hex(0x00C003),  LV_PART_ITEMS | LV_STATE_CHECKED );
lv_obj_set_style_text_opa(lv_tabview_get_tab_btns(ui_Tab_main), 255,  LV_PART_ITEMS| LV_STATE_CHECKED);
lv_obj_set_style_bg_color(lv_tabview_get_tab_btns(ui_Tab_main), lv_color_hex(0xFFFFFF),  LV_PART_ITEMS | LV_STATE_CHECKED );
lv_obj_set_style_bg_opa(lv_tabview_get_tab_btns(ui_Tab_main), 0,  LV_PART_ITEMS| LV_STATE_CHECKED);
lv_obj_set_style_bg_img_src( lv_tabview_get_tab_btns(ui_Tab_main), &ui_img_images_button_checked_png,  LV_PART_ITEMS | LV_STATE_CHECKED );
lv_obj_set_style_border_color(lv_tabview_get_tab_btns(ui_Tab_main), lv_color_hex(0x000000),  LV_PART_ITEMS | LV_STATE_CHECKED );
lv_obj_set_style_border_opa(lv_tabview_get_tab_btns(ui_Tab_main), 0,  LV_PART_ITEMS| LV_STATE_CHECKED);

ui_stat = lv_tabview_add_tab(ui_Tab_main, "STAT");
lv_obj_clear_flag( ui_stat, LV_OBJ_FLAG_SCROLLABLE );    /// Flags

ui_Panel_date = lv_obj_create(ui_stat);
lv_obj_set_width( ui_Panel_date, 131);
lv_obj_set_height( ui_Panel_date, 26);
lv_obj_set_x( ui_Panel_date, -53 );
lv_obj_set_y( ui_Panel_date, 14 );
lv_obj_set_align( ui_Panel_date, LV_ALIGN_CENTER );
lv_obj_clear_flag( ui_Panel_date, LV_OBJ_FLAG_SCROLLABLE );    /// Flags
lv_obj_set_style_radius(ui_Panel_date, 0, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_bg_color(ui_Panel_date, lv_color_hex(0x051E04), LV_PART_MAIN | LV_STATE_DEFAULT );
lv_obj_set_style_bg_opa(ui_Panel_date, 255, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_border_color(ui_Panel_date, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT );
lv_obj_set_style_border_opa(ui_Panel_date, 0, LV_PART_MAIN| LV_STATE_DEFAULT);

ui_Label_date = lv_label_create(ui_Panel_date);
lv_obj_set_width( ui_Label_date, 131);
lv_obj_set_height( ui_Label_date, 31);
lv_obj_set_x( ui_Label_date, 0 );
lv_obj_set_y( ui_Label_date, 1 );
lv_obj_set_align( ui_Label_date, LV_ALIGN_CENTER );
lv_label_set_long_mode(ui_Label_date,LV_LABEL_LONG_SCROLL_CIRCULAR);
lv_label_set_text(ui_Label_date,"Date");
lv_obj_set_style_text_color(ui_Label_date, lv_color_hex(0x00C200), LV_PART_MAIN | LV_STATE_DEFAULT );
lv_obj_set_style_text_opa(ui_Label_date, 255, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_text_align(ui_Label_date, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_text_font(ui_Label_date, &ui_font_J35, LV_PART_MAIN| LV_STATE_DEFAULT);

ui_Panel_battery = lv_obj_create(ui_stat);
lv_obj_set_width( ui_Panel_battery, 131);
lv_obj_set_height( ui_Panel_battery, 22);
lv_obj_set_x( ui_Panel_battery, -53 );
lv_obj_set_y( ui_Panel_battery, 40 );
lv_obj_set_align( ui_Panel_battery, LV_ALIGN_CENTER );
lv_obj_clear_flag( ui_Panel_battery, LV_OBJ_FLAG_SCROLLABLE );    /// Flags
lv_obj_set_style_radius(ui_Panel_battery, 0, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_bg_color(ui_Panel_battery, lv_color_hex(0x051E04), LV_PART_MAIN | LV_STATE_DEFAULT );
lv_obj_set_style_bg_opa(ui_Panel_battery, 255, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_border_color(ui_Panel_battery, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT );
lv_obj_set_style_border_opa(ui_Panel_battery, 0, LV_PART_MAIN| LV_STATE_DEFAULT);

ui_Bar_battery = lv_bar_create(ui_Panel_battery);
lv_obj_set_width( ui_Bar_battery, 104);
lv_obj_set_height( ui_Bar_battery, 12);
lv_obj_set_x( ui_Bar_battery, 9 );
lv_obj_set_y( ui_Bar_battery, 0 );
lv_obj_set_align( ui_Bar_battery, LV_ALIGN_CENTER );
lv_obj_set_style_radius(ui_Bar_battery, 0, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_bg_color(ui_Bar_battery, lv_color_hex(0x182D0C), LV_PART_MAIN | LV_STATE_DEFAULT );
lv_obj_set_style_bg_opa(ui_Bar_battery, 255, LV_PART_MAIN| LV_STATE_DEFAULT);

lv_obj_set_style_radius(ui_Bar_battery, 0, LV_PART_INDICATOR| LV_STATE_DEFAULT);
lv_obj_set_style_bg_color(ui_Bar_battery, lv_color_hex(0x00B700), LV_PART_INDICATOR | LV_STATE_DEFAULT );
lv_obj_set_style_bg_opa(ui_Bar_battery, 255, LV_PART_INDICATOR| LV_STATE_DEFAULT);

ui_Image1 = lv_img_create(ui_Panel_battery);
lv_img_set_src(ui_Image1, &ui_img_images_battery_png);
lv_obj_set_width( ui_Image1, LV_SIZE_CONTENT);  /// 20
lv_obj_set_height( ui_Image1, LV_SIZE_CONTENT);   /// 20
lv_obj_set_x( ui_Image1, -56 );
lv_obj_set_y( ui_Image1, -1 );
lv_obj_set_align( ui_Image1, LV_ALIGN_CENTER );
lv_obj_add_flag( ui_Image1, LV_OBJ_FLAG_ADV_HITTEST );   /// Flags
lv_obj_clear_flag( ui_Image1, LV_OBJ_FLAG_SCROLLABLE );    /// Flags
lv_img_set_zoom(ui_Image1,200);

ui_Label_Time = lv_label_create(ui_stat);
lv_obj_set_width( ui_Label_Time, LV_SIZE_CONTENT);  /// 1
lv_obj_set_height( ui_Label_Time, LV_SIZE_CONTENT);   /// 1
lv_obj_set_x( ui_Label_Time, -53 );
lv_obj_set_y( ui_Label_Time, -26 );
lv_obj_set_align( ui_Label_Time, LV_ALIGN_CENTER );
lv_label_set_text(ui_Label_Time,"00:00");
lv_obj_set_style_text_color(ui_Label_Time, lv_color_hex(0x00C200), LV_PART_MAIN | LV_STATE_DEFAULT );
lv_obj_set_style_text_opa(ui_Label_Time, 255, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_text_font(ui_Label_Time, &ui_font_J70, LV_PART_MAIN| LV_STATE_DEFAULT);

ui_Bar_FL = lv_bar_create(ui_stat);
lv_obj_set_width( ui_Bar_FL, 8);
lv_obj_set_height( ui_Bar_FL, 80);
lv_obj_set_x( ui_Bar_FL, 22 );
lv_obj_set_y( ui_Bar_FL, -6 );
lv_obj_set_align( ui_Bar_FL, LV_ALIGN_CENTER );
lv_obj_set_style_radius(ui_Bar_FL, 0, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_bg_color(ui_Bar_FL, lv_color_hex(0x051E04), LV_PART_MAIN | LV_STATE_DEFAULT );
lv_obj_set_style_bg_opa(ui_Bar_FL, 255, LV_PART_MAIN| LV_STATE_DEFAULT);

lv_obj_set_style_radius(ui_Bar_FL, 0, LV_PART_INDICATOR| LV_STATE_DEFAULT);
lv_obj_set_style_bg_color(ui_Bar_FL, lv_color_hex(0x00B700), LV_PART_INDICATOR | LV_STATE_DEFAULT );
lv_obj_set_style_bg_opa(ui_Bar_FL, 255, LV_PART_INDICATOR| LV_STATE_DEFAULT);

ui_Bar_HI = lv_bar_create(ui_stat);
lv_obj_set_width( ui_Bar_HI, 8);
lv_obj_set_height( ui_Bar_HI, 80);
lv_obj_set_x( ui_Bar_HI, 110 );
lv_obj_set_y( ui_Bar_HI, -6 );
lv_obj_set_align( ui_Bar_HI, LV_ALIGN_CENTER );
lv_obj_set_style_radius(ui_Bar_HI, 0, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_bg_color(ui_Bar_HI, lv_color_hex(0x051E04), LV_PART_MAIN | LV_STATE_DEFAULT );
lv_obj_set_style_bg_opa(ui_Bar_HI, 255, LV_PART_MAIN| LV_STATE_DEFAULT);

lv_obj_set_style_radius(ui_Bar_HI, 0, LV_PART_INDICATOR| LV_STATE_DEFAULT);
lv_obj_set_style_bg_color(ui_Bar_HI, lv_color_hex(0x00B700), LV_PART_INDICATOR | LV_STATE_DEFAULT );
lv_obj_set_style_bg_opa(ui_Bar_HI, 255, LV_PART_INDICATOR| LV_STATE_DEFAULT);

ui_Labe01 = lv_label_create(ui_stat);
lv_obj_set_width( ui_Labe01, LV_SIZE_CONTENT);  /// 1
lv_obj_set_height( ui_Labe01, LV_SIZE_CONTENT);   /// 1
lv_obj_set_x( ui_Labe01, 24 );
lv_obj_set_y( ui_Labe01, 44 );
lv_obj_set_align( ui_Labe01, LV_ALIGN_CENTER );
lv_label_set_text(ui_Labe01,"FL");
lv_obj_set_style_text_color(ui_Labe01, lv_color_hex(0x00C200), LV_PART_MAIN | LV_STATE_DEFAULT );
lv_obj_set_style_text_opa(ui_Labe01, 255, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_text_font(ui_Labe01, &ui_font_J20, LV_PART_MAIN| LV_STATE_DEFAULT);

ui_Labe1 = lv_label_create(ui_stat);
lv_obj_set_width( ui_Labe1, LV_SIZE_CONTENT);  /// 1
lv_obj_set_height( ui_Labe1, LV_SIZE_CONTENT);   /// 1
lv_obj_set_x( ui_Labe1, 110 );
lv_obj_set_y( ui_Labe1, 44 );
lv_obj_set_align( ui_Labe1, LV_ALIGN_CENTER );
lv_label_set_text(ui_Labe1,"HI");
lv_obj_set_style_text_color(ui_Labe1, lv_color_hex(0x00C200), LV_PART_MAIN | LV_STATE_DEFAULT );
lv_obj_set_style_text_opa(ui_Labe1, 255, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_text_font(ui_Labe1, &ui_font_J20, LV_PART_MAIN| LV_STATE_DEFAULT);

ui_Img_stat = lv_img_create(ui_stat);
lv_img_set_src(ui_Img_stat, &ui_img_images_walking_walking_00_png);
lv_obj_set_width( ui_Img_stat, LV_SIZE_CONTENT);  /// 75
lv_obj_set_height( ui_Img_stat, LV_SIZE_CONTENT);   /// 104
lv_obj_set_x( ui_Img_stat, 67 );
lv_obj_set_y( ui_Img_stat, 2 );
lv_obj_set_align( ui_Img_stat, LV_ALIGN_CENTER );
lv_obj_add_flag( ui_Img_stat, LV_OBJ_FLAG_ADV_HITTEST );   /// Flags
lv_obj_clear_flag( ui_Img_stat, LV_OBJ_FLAG_SCROLLABLE );    /// Flags
lv_img_set_zoom(ui_Img_stat,270);

ui_Labe2 = lv_label_create(ui_stat);
lv_obj_set_width( ui_Labe2, LV_SIZE_CONTENT);  /// 1
lv_obj_set_height( ui_Labe2, LV_SIZE_CONTENT);   /// 1
lv_obj_set_x( ui_Labe2, 36 );
lv_obj_set_y( ui_Labe2, -7 );
lv_obj_set_align( ui_Labe2, LV_ALIGN_CENTER );
lv_label_set_text(ui_Labe2,"50");
lv_obj_set_style_text_color(ui_Labe2, lv_color_hex(0x00C200), LV_PART_MAIN | LV_STATE_DEFAULT );
lv_obj_set_style_text_opa(ui_Labe2, 255, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_text_font(ui_Labe2, &ui_font_J20, LV_PART_MAIN| LV_STATE_DEFAULT);

ui_Labe5 = lv_label_create(ui_stat);
lv_obj_set_width( ui_Labe5, LV_SIZE_CONTENT);  /// 1
lv_obj_set_height( ui_Labe5, LV_SIZE_CONTENT);   /// 1
lv_obj_set_x( ui_Labe5, 98 );
lv_obj_set_y( ui_Labe5, -7 );
lv_obj_set_align( ui_Labe5, LV_ALIGN_CENTER );
lv_label_set_text(ui_Labe5,"50");
lv_obj_set_style_text_color(ui_Labe5, lv_color_hex(0x00C200), LV_PART_MAIN | LV_STATE_DEFAULT );
lv_obj_set_style_text_opa(ui_Labe5, 255, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_text_font(ui_Labe5, &ui_font_J20, LV_PART_MAIN| LV_STATE_DEFAULT);

ui_data = lv_tabview_add_tab(ui_Tab_main, "DATA");
lv_obj_clear_flag( ui_data, LV_OBJ_FLAG_SCROLLABLE );    /// Flags

ui_Label_temp = lv_label_create(ui_data);
lv_obj_set_width( ui_Label_temp, 141);
lv_obj_set_height( ui_Label_temp, 50);
lv_obj_set_x( ui_Label_temp, -47 );
lv_obj_set_y( ui_Label_temp, -31 );
lv_obj_set_align( ui_Label_temp, LV_ALIGN_CENTER );
lv_label_set_text(ui_Label_temp,"T:00°C");
lv_obj_set_style_text_color(ui_Label_temp, lv_color_hex(0x00C200), LV_PART_MAIN | LV_STATE_DEFAULT );
lv_obj_set_style_text_opa(ui_Label_temp, 255, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_text_align(ui_Label_temp, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_text_font(ui_Label_temp, &ui_font_J60, LV_PART_MAIN| LV_STATE_DEFAULT);

ui_Label_hum = lv_label_create(ui_data);
lv_obj_set_width( ui_Label_hum, 135);
lv_obj_set_height( ui_Label_hum, 50);
lv_obj_set_x( ui_Label_hum, -47 );
lv_obj_set_y( ui_Label_hum, 20 );
lv_obj_set_align( ui_Label_hum, LV_ALIGN_CENTER );
lv_label_set_text(ui_Label_hum,"H:00%");
lv_obj_set_style_text_color(ui_Label_hum, lv_color_hex(0x00C200), LV_PART_MAIN | LV_STATE_DEFAULT );
lv_obj_set_style_text_opa(ui_Label_hum, 255, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_text_align(ui_Label_hum, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_text_font(ui_Label_hum, &ui_font_J60, LV_PART_MAIN| LV_STATE_DEFAULT);

ui_Bar_Hum = lv_bar_create(ui_data);
lv_obj_set_width( ui_Bar_Hum, 8);
lv_obj_set_height( ui_Bar_Hum, 80);
lv_obj_set_x( ui_Bar_Hum, 111 );
lv_obj_set_y( ui_Bar_Hum, -6 );
lv_obj_set_align( ui_Bar_Hum, LV_ALIGN_CENTER );
lv_obj_set_style_radius(ui_Bar_Hum, 0, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_bg_color(ui_Bar_Hum, lv_color_hex(0x182D0C), LV_PART_MAIN | LV_STATE_DEFAULT );
lv_obj_set_style_bg_opa(ui_Bar_Hum, 255, LV_PART_MAIN| LV_STATE_DEFAULT);

lv_obj_set_style_radius(ui_Bar_Hum, 0, LV_PART_INDICATOR| LV_STATE_DEFAULT);
lv_obj_set_style_bg_color(ui_Bar_Hum, lv_color_hex(0x00C200), LV_PART_INDICATOR | LV_STATE_DEFAULT );
lv_obj_set_style_bg_opa(ui_Bar_Hum, 255, LV_PART_INDICATOR| LV_STATE_DEFAULT);

ui_Bar_Temp = lv_bar_create(ui_data);
lv_obj_set_width( ui_Bar_Temp, 8);
lv_obj_set_height( ui_Bar_Temp, 80);
lv_obj_set_x( ui_Bar_Temp, 22 );
lv_obj_set_y( ui_Bar_Temp, -6 );
lv_obj_set_align( ui_Bar_Temp, LV_ALIGN_CENTER );
lv_obj_set_style_radius(ui_Bar_Temp, 0, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_bg_color(ui_Bar_Temp, lv_color_hex(0x182D0C), LV_PART_MAIN | LV_STATE_DEFAULT );
lv_obj_set_style_bg_opa(ui_Bar_Temp, 255, LV_PART_MAIN| LV_STATE_DEFAULT);

lv_obj_set_style_radius(ui_Bar_Temp, 0, LV_PART_INDICATOR| LV_STATE_DEFAULT);
lv_obj_set_style_bg_color(ui_Bar_Temp, lv_color_hex(0x00C200), LV_PART_INDICATOR | LV_STATE_DEFAULT );
lv_obj_set_style_bg_opa(ui_Bar_Temp, 255, LV_PART_INDICATOR| LV_STATE_DEFAULT);

ui_Labe3 = lv_label_create(ui_data);
lv_obj_set_width( ui_Labe3, LV_SIZE_CONTENT);  /// 1
lv_obj_set_height( ui_Labe3, LV_SIZE_CONTENT);   /// 1
lv_obj_set_x( ui_Labe3, 23 );
lv_obj_set_y( ui_Labe3, 45 );
lv_obj_set_align( ui_Labe3, LV_ALIGN_CENTER );
lv_label_set_text(ui_Labe3,"T");
lv_obj_set_style_text_color(ui_Labe3, lv_color_hex(0x00C200), LV_PART_MAIN | LV_STATE_DEFAULT );
lv_obj_set_style_text_opa(ui_Labe3, 255, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_text_font(ui_Labe3, &ui_font_J20, LV_PART_MAIN| LV_STATE_DEFAULT);

ui_Labe4 = lv_label_create(ui_data);
lv_obj_set_width( ui_Labe4, LV_SIZE_CONTENT);  /// 1
lv_obj_set_height( ui_Labe4, LV_SIZE_CONTENT);   /// 1
lv_obj_set_x( ui_Labe4, 111 );
lv_obj_set_y( ui_Labe4, 44 );
lv_obj_set_align( ui_Labe4, LV_ALIGN_CENTER );
lv_label_set_text(ui_Labe4,"H");
lv_obj_set_style_text_color(ui_Labe4, lv_color_hex(0x00C200), LV_PART_MAIN | LV_STATE_DEFAULT );
lv_obj_set_style_text_opa(ui_Labe4, 255, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_text_font(ui_Labe4, &ui_font_J20, LV_PART_MAIN| LV_STATE_DEFAULT);

ui_Img_data = lv_img_create(ui_data);
lv_img_set_src(ui_Img_data, &ui_img_images_thumpsup_thumpsup_00_png);
lv_obj_set_width( ui_Img_data, LV_SIZE_CONTENT);  /// 75
lv_obj_set_height( ui_Img_data, LV_SIZE_CONTENT);   /// 104
lv_obj_set_x( ui_Img_data, 65 );
lv_obj_set_y( ui_Img_data, 2 );
lv_obj_set_align( ui_Img_data, LV_ALIGN_CENTER );
lv_obj_add_flag( ui_Img_data, LV_OBJ_FLAG_ADV_HITTEST );   /// Flags
lv_obj_clear_flag( ui_Img_data, LV_OBJ_FLAG_SCROLLABLE );    /// Flags
lv_img_set_zoom(ui_Img_data,270);

}
