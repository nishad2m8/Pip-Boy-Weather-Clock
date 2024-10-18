SET(SOURCES screens/ui_Screen1.c
    ui.c
    components/ui_comp_hook.c
    ui_helpers.c
    images/ui_img_images_button_checked_png.c
    images/ui_img_images_walking_png_frames_walking_000_png.c
    images/ui_img_images_compass_png.c
    images/ui_img_images_battery_png.c
    images/ui_img_images_thumpsup_png_frames_thumpsup_000_png.c
    images/ui_img_images_vault_logo_png.c
    images/ui_img_images_thumpsup_png_frames_thumpsup_001_png.c
    images/ui_img_images_thumpsup_png_frames_thumpsup_002_png.c
    images/ui_img_images_thumpsup_png_frames_thumpsup_003_png.c
    images/ui_img_images_thumpsup_png_frames_thumpsup_004_png.c
    images/ui_img_images_thumpsup_png_frames_thumpsup_005_png.c
    images/ui_img_images_thumpsup_png_frames_thumpsup_006_png.c
    images/ui_img_images_thumpsup_png_frames_thumpsup_007_png.c
    images/ui_img_images_thumpsup_png_frames_thumpsup_008_png.c
    images/ui_img_images_thumpsup_png_frames_thumpsup_009_png.c
    images/ui_img_images_thumpsup_png_frames_thumpsup_010_png.c
    images/ui_img_images_walking_png_frames_walking_001_png.c
    images/ui_img_images_walking_png_frames_walking_002_png.c
    images/ui_img_images_walking_png_frames_walking_003_png.c
    images/ui_img_images_walking_png_frames_walking_004_png.c
    images/ui_img_images_walking_png_frames_walking_005_png.c
    images/ui_img_images_walking_png_frames_walking_006_png.c
    images/ui_img_images_walking_png_frames_walking_007_png.c
    images/ui_img_images_walking_png_frames_walking_008_png.c
    fonts/ui_font_J140.c
    fonts/ui_font_J30.c
    fonts/ui_font_J35.c
    fonts/ui_font_J60.c)

add_library(ui ${SOURCES})
