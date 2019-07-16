/**
 * @file lv_ex_templ.c
 *
 */

/*********************
 *      INCLUDES
 *********************/
#include "lvgl/lvgl.h"
#include <stdio.h>

/*********************
 *      DEFINES
 *********************/

/**********************
 *      TYPEDEFS
 **********************/

/**********************
 *  STATIC PROTOTYPES
 **********************/
static void kb_event_cb(lv_obj_t * event_kb, lv_event_t event);
static void ta_event_cb(lv_obj_t * ta, lv_event_t event);

/**********************
 *  STATIC VARIABLES
 **********************/

static lv_obj_t * kb;
/**********************
 *      MACROS
 **********************/

/**********************
 *   GLOBAL FUNCTIONS
 **********************/

void lv_ex_ta_2(void)
{
    /* Create the password box */
    lv_obj_t * pwd_ta = lv_ta_create(lv_scr_act(), NULL);
    lv_ta_set_text(pwd_ta, "");
    lv_ta_set_pwd_mode(pwd_ta, true);
    lv_ta_set_one_line(pwd_ta, true);
    lv_obj_set_width(pwd_ta, LV_HOR_RES / 2 - 20);
    lv_obj_set_pos(pwd_ta, 5, 20);
    lv_obj_set_event_cb(pwd_ta, ta_event_cb);
    
    /* Create a label and position it above the text box */
    lv_obj_t * pwd_label = lv_label_create(lv_scr_act(), NULL);
    lv_label_set_text(pwd_label, "Password:");
    lv_obj_align(pwd_label, pwd_ta, LV_ALIGN_OUT_TOP_LEFT, 0, 0);
    
    
    /* Create the one-line mode text area */
    lv_obj_t * oneline_ta = lv_ta_create(lv_scr_act(), pwd_ta);
    lv_ta_set_pwd_mode(oneline_ta, false);
    lv_ta_set_cursor_type(oneline_ta, LV_CURSOR_LINE | LV_CURSOR_HIDDEN);
    lv_obj_align(oneline_ta, NULL, LV_ALIGN_IN_TOP_RIGHT, -5, 20);
    
    /* Create a label and position it above the text box */
    lv_obj_t * oneline_label = lv_label_create(lv_scr_act(), NULL);
    lv_label_set_text(oneline_label, "Text:");
    lv_obj_align(oneline_label, oneline_ta, LV_ALIGN_OUT_TOP_LEFT, 0, 0);

    /* Create a keyboard and make it fill the width of the above text areas */
    kb = lv_kb_create(lv_scr_act(), NULL);
    lv_obj_set_pos(kb, 5, 90);
    lv_obj_set_event_cb(kb, kb_event_cb); /* Setting a custom event handler stops the keyboard from closing automatically */
    lv_obj_set_size(kb,  LV_HOR_RES - 10, 140);
    
    lv_kb_set_ta(kb, pwd_ta); /* Focus it on one of the text areas to start */
    lv_kb_set_cursor_manage(kb, true); /* Automatically show/hide cursors on text areas */
}

/**********************
 *   STATIC FUNCTIONS
 **********************/

static void kb_event_cb(lv_obj_t * event_kb, lv_event_t event)
{
    /* Just call the regular event handler */
    lv_kb_def_event_cb(event_kb, event);

}
static void ta_event_cb(lv_obj_t * ta, lv_event_t event)
{
    if(event == LV_EVENT_CLICKED) {
        /* Focus on the clicked text area */
        if(kb != NULL)
            lv_kb_set_ta(kb, ta);
    }

    else if(event == LV_EVENT_INSERT) {
        const char * str = lv_event_get_data();
        if(str[0] == '\n') {
            printf("Ready\n");
        }
    }
}
