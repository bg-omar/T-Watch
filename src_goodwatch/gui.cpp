/*
 * Copyright (c) 2020 Alex Goodyear
 * Derived from ...
Copyright (c) 2019 lewis he
This is just a demonstration. Most of the functions are not implemented.
The main implementation is low-power standby. 
The off-screen standby (not deep sleep) current is about 4mA.
Select standard motherboard and standard backplane for testing.
Created by Lewis he on October 10, 2019.
*/

#include "config.h"
#include <Arduino.h>
#include <time.h>
#include <SPI.h>
#include "gui.h"
#include <WiFi.h>
#include "string.h"
#include <Ticker.h>

LV_FONT_DECLARE(Ubuntu);

LV_IMG_DECLARE(bg2);
LV_IMG_DECLARE(foot_16px);
LV_IMG_DECLARE(homerFace);
LV_IMG_DECLARE(hourHand);
LV_IMG_DECLARE(minHand);
LV_IMG_DECLARE(secHand);
LV_IMG_DECLARE(eye);

LV_IMG_DECLARE(wifi);
LV_IMG_DECLARE(on);
LV_IMG_DECLARE(off);
LV_IMG_DECLARE(level1);
LV_IMG_DECLARE(level2);
LV_IMG_DECLARE(level3);
LV_IMG_DECLARE(modules); // AKA About!

extern EventGroupHandle_t g_event_group;
extern QueueHandle_t g_event_queue_handle;

static lv_style_t settingStyle;

static lv_obj_t *mainBar = nullptr;

static lv_style_t mainStyle;

static lv_obj_t *menuBtn = nullptr;
static lv_obj_t *torchLabel = nullptr;

static uint8_t globalIndex = 0;

static void lv_update_task(struct _lv_task_t *);
static void lv_battery_task(struct _lv_task_t *);

static int createOriginalFace (int);
static int updateOriginalFace (int);
static int createHomerFace (int);
static int createWiFi (int);
static int createWiFiSwitches (int);
static int createAbout (int);
static int createAboutInfo (int);

#ifdef DEBUG_EVENTS
#define DEBUG_EVENTS
/*
 * This is for debugging the LVGL library, requires LV_USE_LOG setting in lv_conf.h
 */
void my_log_cb (lv_log_level_t level, const char * file, int line, const char * fn_name, const char * dsc)
{
  /*Send the logs via serial port*/
  if(level == LV_LOG_LEVEL_ERROR) Serial.print("ERROR: ");
  if(level == LV_LOG_LEVEL_WARN)  Serial.print("WARNING: ");
  if(level == LV_LOG_LEVEL_INFO)  Serial.print("INFO: ");
  if(level == LV_LOG_LEVEL_TRACE) Serial.print("TRACE: ");

  Serial.printf("%s:%d:%s: %s\n", file, line, fn_name, dsc);
}

static char *decodeEvent (lv_event_t event);

static void my_test_event_cb (lv_obj_t * obj, lv_event_t event)
{
  log_d ("obj=%p, event=%d: %s", obj, event, decodeEvent (event));
}
#endif  // DEBUG_EVENTS.

static char *decodeEvent (lv_event_t event)
{
    switch(event) {
        case LV_EVENT_PRESSED:
            return ("LV_EVENT_PRESSED");

        case LV_EVENT_PRESSING:
            return ("LV_EVENT_PRESSING");

        case LV_EVENT_PRESS_LOST:
            return ("LV_EVENT_PRESS_LOST");

        case LV_EVENT_SHORT_CLICKED:
            return ("LV_EVENT_SHORT_CLICKED");

        case LV_EVENT_CLICKED:
            return ("LV_EVENT_CLICKED");

        case LV_EVENT_LONG_PRESSED:
            return ("LV_EVENT_LONG_PRESSED");

        case LV_EVENT_LONG_PRESSED_REPEAT:
            return ("LV_EVENT_LONG_PRESSED_REPEAT");

        case LV_EVENT_RELEASED:
            return ("LV_EVENT_RELEASED");

        case LV_EVENT_DRAG_BEGIN:
            return ("LV_EVENT_DRAG_BEGIN");

        case LV_EVENT_DRAG_END:
            return ("LV_EVENT_DRAG_END");

        case LV_EVENT_DRAG_THROW_BEGIN:
            return ("LV_EVENT_DRAG_THROW_BEGIN");

        case LV_EVENT_GESTURE:
            log_d ("dir=%d\n", (int)lv_indev_get_gesture_dir(lv_indev_get_act()));
            return ("LV_EVENT_GESTURE");

        case LV_EVENT_KEY:
            return ("LV_EVENT_KEY");

        case LV_EVENT_FOCUSED:
            return ("LV_EVENT_FOCUSED");

        case LV_EVENT_DEFOCUSED:
            return ("LV_EVENT_DEFOCUSED");

        case LV_EVENT_LEAVE:
            return ("LV_EVENT_LEAVE");

        case LV_EVENT_VALUE_CHANGED:
            return ("LV_EVENT_VALUE_CHANGED");

        case LV_EVENT_INSERT:
            return ("LV_EVENT_INSERT");

        case LV_EVENT_REFRESH:
            return ("LV_EVENT_REFRESH");

        case LV_EVENT_APPLY:
            return ("LV_EVENT_APPLY");

        case LV_EVENT_CANCEL:
            return ("LV_EVENT_CANCEL");

        case LV_EVENT_DELETE:
            return ("LV_EVENT_DELETE");

        default:
            return ("Unknown event");
    }
}

class StatusBar
{
    typedef struct {
        bool vaild;
        lv_obj_t *icon;
    } lv_status_bar_t;
public:
    StatusBar()
    {
        memset(_array, 0, sizeof(_array));
    }
    void createIcons(lv_obj_t *par)
    {
        _par = par;

        static lv_style_t barStyle;
        lv_style_init(&barStyle);
        lv_style_set_radius(&barStyle, LV_OBJ_PART_MAIN, 0);
        lv_style_set_bg_color(&barStyle, LV_OBJ_PART_MAIN, LV_COLOR_GRAY);
        lv_style_set_bg_opa(&barStyle, LV_OBJ_PART_MAIN, LV_OPA_20);
        lv_style_set_border_width(&barStyle, LV_OBJ_PART_MAIN, 0);
        lv_style_set_text_color(&barStyle, LV_OBJ_PART_MAIN, LV_COLOR_WHITE);
        lv_style_set_image_recolor(&barStyle, LV_OBJ_PART_MAIN, LV_COLOR_WHITE);

        _bar = lv_cont_create(_par, NULL);
        lv_obj_set_size(_bar,  LV_HOR_RES, _barHeight);
        lv_obj_add_style(_bar, LV_OBJ_PART_MAIN, &barStyle);

        _array[0].icon = lv_label_create(_bar, NULL);
        lv_label_set_text(_array[0].icon, "100%");

        _array[1].icon = lv_img_create(_bar, NULL);
        lv_img_set_src(_array[1].icon, LV_SYMBOL_BATTERY_FULL);

        _array[2].icon = lv_img_create(_bar, NULL);
        lv_img_set_src(_array[2].icon, LV_SYMBOL_WIFI);
        lv_obj_set_hidden(_array[2].icon, true);

        _array[3].icon = lv_img_create(_bar, NULL);
        lv_img_set_src(_array[3].icon, LV_SYMBOL_BLUETOOTH);
        lv_obj_set_hidden(_array[3].icon, true);

        //step counter
        _array[4].icon = lv_img_create(_bar, NULL);
        lv_img_set_src(_array[4].icon, &foot_16px);
        lv_obj_align(_array[4].icon, _bar, LV_ALIGN_IN_LEFT_MID, 10, 0);

        _array[5].icon = lv_label_create(_bar, NULL);
        lv_label_set_text(_array[5].icon, "00000");
        lv_obj_align(_array[5].icon, _array[4].icon, LV_ALIGN_OUT_RIGHT_MID, 5, 0);

        _array[6].icon = lv_label_create(_bar, NULL);
        lv_label_set_text(_array[6].icon, THIS_VERSION_STR);
        lv_obj_align(_array[6].icon, _array[5].icon, LV_ALIGN_OUT_RIGHT_MID, 5, 0);
        
        refresh();
    }

    void setStepCounter(uint32_t counter)
    {
        lv_label_set_text(_array[5].icon, String(counter).c_str());
        lv_obj_align(_array[5].icon, _array[4].icon, LV_ALIGN_OUT_RIGHT_MID, 5, 0);
    }

    void updateLevel(int level)
    {
        lv_label_set_text(_array[0].icon, (String(level) + "%").c_str());
        refresh();
    }

    void updateBatteryIcon(lv_icon_battery_t icon)
    {
        const char *icons[6] = {LV_SYMBOL_BATTERY_EMPTY, LV_SYMBOL_BATTERY_1, LV_SYMBOL_BATTERY_2, LV_SYMBOL_BATTERY_3, LV_SYMBOL_BATTERY_FULL, LV_SYMBOL_CHARGE};
        lv_img_set_src(_array[1].icon, icons[icon]);
        refresh();
    }

    void show(lv_icon_status_bar_t icon)
    {
        lv_obj_set_hidden(_array[icon].icon, false);
        refresh();
    }

    void hidden(lv_icon_status_bar_t icon)
    {
        lv_obj_set_hidden(_array[icon].icon, true);
        refresh();
    }
    uint8_t height()
    {
        return _barHeight;
    }
    lv_obj_t *self()
    {
        return _bar;
    }
private:
    void refresh()
    {
        int prev;
        for (int i = 0; i < 4; i++) {
            if (!lv_obj_get_hidden(_array[i].icon)) {
                if (i == LV_STATUS_BAR_BATTERY_LEVEL) {
                    lv_obj_align(_array[i].icon, NULL, LV_ALIGN_IN_RIGHT_MID, 0, 0);
                } else {
                    lv_obj_align(_array[i].icon, _array[prev].icon, LV_ALIGN_OUT_LEFT_MID, iconOffset, 0);
                }
                prev = i;
            }
        }
    };
    lv_obj_t *_bar = nullptr;
    lv_obj_t *_par = nullptr;
    uint8_t _barHeight = 30;
    lv_status_bar_t _array[7];
    const int8_t iconOffset = -5;
};

StatusBar bar;

TileDesc_t tileDesc[] = {{0, createOriginalFace}, {1, createHomerFace},
	                 {0, createWiFi}, {1, createWiFiSwitches},
	                 {0, createAbout}, {1, createAboutInfo}};

int numDescTiles = sizeof (tileDesc) / sizeof (TileDesc_t);

#define TILE_OFFSET 2  // This value must be the number of columns.

lv_obj_t *tileView;
lv_point_t *tileMap;

static int32_t lastIdx = 0;

static void tileViewEvent_cb (lv_obj_t * obj, lv_event_t event)
{
  log_d ("obj=%p, event=%d: %s", obj, event, decodeEvent (event));

  if(event == LV_EVENT_VALUE_CHANGED)
  {
    /*
    ** The documentation says that this is uint32_t * but I want it signed!
    */
    int32_t idx = *((int32_t *)lv_event_get_data ());

    log_i ("tileViewChanged: was=%d, is=%d", lastIdx, idx);

    /*
    ** Do not remove watch time updates when moving to other features.
    */
    if (!((lastIdx == 0) && (tileDesc[idx].row == 1)))
    {
      if (tileDesc[lastIdx].onExit != nullptr) tileDesc[lastIdx].onExit (lastIdx);
    }
    else
    {
      log_d ("onExit for idx=%d ignored", lastIdx);
    }

    /*
    ** Do not add watch time updates when moving from other features.
    */
    if (!((idx == 0) && (tileDesc[lastIdx].row == 1)))
    {
      if (tileDesc[idx].onEntry != nullptr) tileDesc[idx].onEntry (idx);
    }
    else
    {
      log_d ("onEntry for idx=%d ignored", idx);
    }

    /*
    ** Ensure that movement between tile rows only occurs in column zero.
    */
    if ((tileMap[idx].x == 0) && (tileMap[lastIdx].y != tileMap[idx].y))
    {
      uint32_t i;

      for (i = lastIdx + 1; tileMap[lastIdx].y == tileMap[i].y; i++)
      {
        tileMap[i].x += TILE_OFFSET;
      }

      for (i = idx + 1; tileMap[idx].y == tileMap[i].y; i++)
      {
        tileMap[i].x -= TILE_OFFSET;
      }

      /*
      ** Refresh the valid positions to force the tile to re-evaluate
      ** valid tile movements.
      */
      lv_tileview_set_valid_positions (obj, tileMap, numDescTiles);
    }

    lastIdx = idx;
  }
}

static void watchFaceEvent_cb (lv_obj_t * obj, lv_event_t event)
{
  log_d ("obj=%p, event=%d: %s", obj, event, decodeEvent (event));

  if ((event == LV_EVENT_LONG_PRESSED) &&
           (tileDesc[lastIdx].row == 0) &&
           (tileDesc[lastIdx].col != 0))
  {
    /*
    ** A new watch face has been selected.
    */
    log_i ("New watch face selected idx=%d, col=%d", lastIdx, tileDesc[lastIdx].col);

    /*
     * In preview mode, both the default face (idx == 0) and the currently viewed face have
     * task updates registered - remove the preview ready for the face shuffle.
     */
    tileDesc[lastIdx].onExit (lastIdx);
    
    /*
    ** Alter the tileView to reflect the new selection.
    */
    lv_obj_set_pos (tileDesc[0].tile, LV_HOR_RES * tileDesc[lastIdx].col,
                    LV_VER_RES * tileDesc[lastIdx].row);

    lv_obj_set_pos (tileDesc[lastIdx].tile, 0, 0);

    /*
    ** row & col remain with the array index position and create is not
    ** required during run-time.
    */
    int (*tfunc)(int) = tileDesc[lastIdx].onEntry;
    tileDesc[lastIdx].onEntry = tileDesc[0].onEntry;
    tileDesc[0].onEntry = tfunc;

    tfunc = tileDesc[lastIdx].onExit;
    tileDesc[lastIdx].onExit = tileDesc[0].onExit;
    tileDesc[0].onExit = tfunc;

    tfunc = tileDesc[lastIdx].onUpdate;
    tileDesc[lastIdx].onUpdate = tileDesc[0].onUpdate;
    tileDesc[0].onUpdate = tfunc;

    lv_obj_t *tobj = tileDesc[lastIdx].tile;
    tileDesc[lastIdx].tile = tileDesc[0].tile;
    tileDesc[0].tile = tobj;

    void *tdata = tileDesc[lastIdx].data;
    tileDesc[lastIdx].data = tileDesc[0].data;
    tileDesc[0].data = tdata;

    /*
    ** Finally, set the new tile position to 0,0 (this will cause an
    ** LV_EVENT_VALUE_CHANGED to be generated).
    */
    lv_tileview_set_tile_act (tileView, 0, 0, LV_ANIM_OFF);
    
    TTGOClass *ttgo = TTGOClass::getWatch();
    ttgo->shake ();
  }
}

void setupGui()
{
    //lv_log_register_print_cb((lv_log_print_g_cb_t)my_log_cb);

    lv_obj_t *scr = lv_scr_act();

    log_d ("called");
    
    lv_style_init(&settingStyle);
    lv_style_set_radius(&settingStyle, LV_OBJ_PART_MAIN, 0);
    lv_style_set_bg_color(&settingStyle, LV_OBJ_PART_MAIN, LV_COLOR_GRAY);
    lv_style_set_bg_opa(&settingStyle, LV_OBJ_PART_MAIN, LV_OPA_0);
    lv_style_set_border_width(&settingStyle, LV_OBJ_PART_MAIN, 0);
    lv_style_set_text_color(&settingStyle, LV_OBJ_PART_MAIN, LV_COLOR_WHITE);
    lv_style_set_image_recolor(&settingStyle, LV_OBJ_PART_MAIN, LV_COLOR_WHITE);
    
    /* 
     * Create the torch and ensure that it is at the back of all other widgets.
     * I tried creating a label and a container before finally stumbling upon
     * the positioning functionality I wanted with a button.
     */
    torchLabel = lv_btn_create (scr, NULL);
    static lv_style_t torchStyle;
    lv_style_copy(&torchStyle, &settingStyle);
    lv_style_set_bg_color(&torchStyle, LV_OBJ_PART_MAIN, LV_COLOR_WHITE);
    lv_style_set_bg_opa(&torchStyle, LV_OBJ_PART_MAIN, 255);
    lv_style_set_text_color(&torchStyle, LV_OBJ_PART_MAIN, LV_COLOR_RED);
    lv_obj_add_style(torchLabel, LV_OBJ_PART_MAIN, &torchStyle);
    lv_obj_set_size(torchLabel, LV_HOR_RES, LV_VER_RES - 30);
    lv_obj_move_background(torchLabel);
    lv_obj_set_pos(torchLabel, 0, 30);
    lv_obj_t *l = lv_label_create (torchLabel, NULL);

    lv_label_set_text(l, "  TORCH MODE  ");
    lv_obj_align(l, NULL, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_user_data(torchLabel, l);
    /*
     * There seems to be an LVGL buglet that allows the scrolling label to bleed through
     * to the tile menu. Hiding it makes the ghost image disappear.
     */
    //lv_obj_set_hidden (l, true);

    lv_obj_t *img_bin = lv_img_create (scr, NULL);
    lv_img_set_src (img_bin, &bg2);
    lv_obj_set_size (img_bin, LV_HOR_RES, LV_VER_RES);
    lv_obj_align (img_bin, NULL, LV_ALIGN_CENTER, 0, 0);

    tileView = lv_tileview_create (img_bin, NULL);
    lv_obj_add_style (tileView, LV_OBJ_PART_MAIN, &settingStyle);
    lv_obj_align (tileView, NULL, LV_ALIGN_CENTER, 0, 0);
    
    lv_tileview_set_edge_flash (tileView, true);
    lv_page_set_scrlbar_mode(tileView, LV_SCRLBAR_MODE_OFF);
    
    tileMap  = (lv_point_t *)calloc (numDescTiles, sizeof (lv_point_t));

    int row = -1;

    for (int idx = 0; idx < numDescTiles; idx++ )
    {
      if (tileDesc[idx].col == 0)
      {
        row++;
      }

      log_d ("- for loop row=%d col=%d idx=%d", row, tileDesc[idx].col, idx);

      tileDesc[idx].tile = lv_cont_create (tileView, NULL);
      lv_obj_set_size (tileDesc[idx].tile, LV_HOR_RES, LV_VER_RES);
      lv_obj_add_style (tileDesc[idx].tile, LV_OBJ_PART_MAIN, &settingStyle);
      lv_obj_set_pos (tileDesc[idx].tile, LV_HOR_RES * tileDesc[idx].col, LV_VER_RES * row); 

      tileDesc[idx].row = row;

      lv_tileview_add_element (tileView, tileDesc[idx].tile);

      tileDesc[idx].onEntry = nullptr;
      tileDesc[idx].onExit  = nullptr;

      tileDesc[idx].create (idx);

      /*
      ** Only enable movement for column zero and the watch face row.
      */
      tileMap[idx].x = tileDesc[idx].col + ((row == 0) || (tileDesc[idx].col == 0) ? 0 : TILE_OFFSET);

      tileMap[idx].y = row;
    }

    lv_tileview_set_valid_positions (tileView, tileMap, numDescTiles);

    lv_obj_set_event_cb (tileView, tileViewEvent_cb);

    lv_tileview_set_tile_act (tileView, 0, 0, LV_ANIM_OFF);
}

typedef struct
{
  lv_task_t *timeTask;
  lv_task_t *battTask;
  lv_obj_t *timeLabel;
  lv_obj_t *dateLabel;
} OriginalFaceData;

static int onEntryOriginalFace (int idx)
{
  OriginalFaceData *ofd = (OriginalFaceData *)(tileDesc[idx].data);

  log_d ("idx=%d", idx);

  if (ofd->timeTask == nullptr)
  {
    ofd->timeTask = lv_task_create(lv_update_task, 1000, LV_TASK_PRIO_LOWEST, (void *)idx);
  }
}

static int onExitOriginalFace (int idx)
{
  OriginalFaceData *ofd = (OriginalFaceData *)(tileDesc[idx].data);

  log_d ("idx=%d", idx);

  if (ofd->timeTask != nullptr)
  {
    lv_task_del (ofd->timeTask);
    ofd->timeTask = nullptr;
  }
}

static int createOriginalFace (int idx)
{
    lv_obj_t *parentObj = tileDesc[idx].tile;
    lv_obj_t *timeLabel;
    lv_obj_t *dateLabel;

    log_d ("idx=%d", idx);

    //! bar
    bar.createIcons(parentObj);
    updateBatteryLevel();
    lv_icon_battery_t icon = LV_ICON_CALCULATION;

    TTGOClass *ttgo = TTGOClass::getWatch();

    if (ttgo->power->isChargeing()) {
        icon = LV_ICON_CHARGE;
    }

    updateBatteryIcon(icon);

    //! main
    lv_style_init(&mainStyle);
    lv_style_set_radius(&mainStyle, LV_OBJ_PART_MAIN, 0);
    lv_style_set_bg_color(&mainStyle, LV_OBJ_PART_MAIN, LV_COLOR_GRAY);
    lv_style_set_bg_opa(&mainStyle, LV_OBJ_PART_MAIN, LV_OPA_0);
    lv_style_set_border_width(&mainStyle, LV_OBJ_PART_MAIN, 0);
    lv_style_set_text_color(&mainStyle, LV_OBJ_PART_MAIN, LV_COLOR_WHITE);
    lv_style_set_image_recolor(&mainStyle, LV_OBJ_PART_MAIN, LV_COLOR_WHITE);

    mainBar = lv_cont_create(parentObj, NULL);
    lv_obj_set_size(mainBar,  LV_HOR_RES, LV_VER_RES - bar.height());
    lv_obj_add_style(mainBar, LV_OBJ_PART_MAIN, &mainStyle);
    
    lv_obj_align(mainBar, bar.self(), LV_ALIGN_OUT_BOTTOM_MID, 0, 0);

    //! Time
    static lv_style_t timeStyle;
    static lv_style_t dateStyle;
    lv_style_copy(&timeStyle, &mainStyle);
    lv_style_set_text_font (&timeStyle, LV_STATE_DEFAULT, &Ubuntu);
    lv_style_copy(&dateStyle, &mainStyle);
    lv_style_set_text_letter_space (&timeStyle, LV_STATE_DEFAULT, -2);

    timeLabel = lv_label_create(mainBar, NULL);
    lv_obj_add_style(timeLabel, LV_OBJ_PART_MAIN, &timeStyle);
    dateLabel = lv_label_create(mainBar, NULL);
    lv_obj_add_style(dateLabel, LV_OBJ_PART_MAIN, &dateStyle);
    //lv_label_set_long_mode(dateLabel, LV_LABEL_LONG_SROLL_CIRC);
    
#ifdef DEBUG_EVENTS    
    lv_obj_set_gesture_parent(mainBar,0);
    lv_obj_set_event_cb(mainBar, my_test_event_cb);
#endif

    lv_tileview_add_element (tileView, mainBar);

    lv_obj_set_event_cb (mainBar, watchFaceEvent_cb);

    tileDesc[idx].onEntry  = onEntryOriginalFace;
    tileDesc[idx].onExit   = onExitOriginalFace;
    tileDesc[idx].onUpdate = updateOriginalFace;

    tileDesc[idx].data = malloc (sizeof (OriginalFaceData));

    ((OriginalFaceData *)(tileDesc[idx].data))->timeLabel = timeLabel;
    ((OriginalFaceData *)(tileDesc[idx].data))->dateLabel = dateLabel;
    ((OriginalFaceData *)(tileDesc[idx].data))->timeTask = nullptr;

    updateTime();
}

void updateStepCounter(uint32_t counter)
{
    bar.setStepCounter(counter);
}

static int updateOriginalFace (int idx)
{
    OriginalFaceData *ofd = (OriginalFaceData *)(tileDesc[idx].data);
    lv_obj_t *timeLabel = ofd->timeLabel;
    lv_obj_t *dateLabel = ofd->dateLabel;
    time_t now;
    struct tm  info;
    char buf[64];
    TTGOClass *ttgo = TTGOClass::getWatch();
    
    time(&now);
    localtime_r(&now, &info);
    strftime(buf, sizeof(buf), "%H:%M:%S", &info);
    lv_label_set_text(timeLabel, buf);
    lv_obj_align(timeLabel, NULL, LV_ALIGN_IN_TOP_MID, 0, 10);
    strftime(buf, sizeof(buf), "%a %d/%m/%Y", &info);
    lv_label_set_text (dateLabel, buf);
    lv_obj_align(dateLabel, NULL, LV_ALIGN_CENTER, 0, 0);

    if (screenTimeout == defaultScreenTimeout)
    {
      if ((info.tm_hour > 22) || (info.tm_hour < 8))
      {
        ttgo->setBrightness(8);
      }
      else
      {
        ttgo->setBrightness(64);
      }
    }
}

void updateTime()
{
  tileDesc[0].onUpdate (0);
}

void torchOn ()
{
  //lv_obj_set_hidden ((lv_obj_t*)lv_obj_get_user_data (torchLabel), false);
  lv_obj_move_foreground(torchLabel);
}

void torchOff ()
{
  screenTimeout = defaultScreenTimeout = DEFAULT_SCREEN_TIMEOUT;
  lv_obj_move_background(torchLabel);
  //lv_obj_set_hidden ((lv_obj_t*)lv_obj_get_user_data (torchLabel), true);
  updateTime ();
}

void updateBatteryLevel()
{
    TTGOClass *ttgo = TTGOClass::getWatch();
    int p = ttgo->power->getBattPercentage();
    bar.updateLevel(p);
}

void updateBatteryIcon(lv_icon_battery_t icon)
{
    if (icon <= LV_ICON_CALCULATION) {
        TTGOClass *ttgo = TTGOClass::getWatch();
        int level = ttgo->power->getBattPercentage();
        if (level > 95)icon = LV_ICON_BAT_FULL;
        else if (level > 65)icon = LV_ICON_BAT_3;
        else if (level > 40)icon = LV_ICON_BAT_2;
        else if (level > 10)icon = LV_ICON_BAT_1;
        else icon = LV_ICON_BAT_EMPTY;
    }
    bar.updateBatteryIcon(icon);
}


static void lv_update_task(struct _lv_task_t *data)
{
  log_d ("update %d", (int)(data->user_data));

  tileDesc[(int)(data->user_data)].onUpdate ((int)(data->user_data));
}

static void lv_battery_task(struct _lv_task_t *data)
{
    updateBatteryLevel();
}

typedef struct
{
  lv_task_t *timeTask;
  lv_obj_t *hourHand;
  lv_obj_t *minHand;
  lv_obj_t *secHand;
  lv_obj_t *hourShadow;
  lv_obj_t *minShadow;
  lv_obj_t *secShadow;
  lv_obj_t *leftEye;
  lv_obj_t *rightEye;
} HomerFaceData_t;

static int updateHomerFace (int idx)
{
  time_t now;
  struct tm info;
  HomerFaceData_t *hfd = (HomerFaceData_t *)(tileDesc[idx].data);
  static int lastMin = 61;
  
  log_d ("idx=%d", idx);

  time (&now);
  localtime_r (&now, &info);

  int sec  = 60 * info.tm_sec;

  lv_img_set_angle (hfd->leftEye, sec);
  lv_img_set_angle (hfd->rightEye, sec);

  if (info.tm_min != lastMin)
  {
    lastMin = info.tm_min;
    
    int hour = (300 * (info.tm_hour % 12)) + (5 * lastMin);
    int min  = 60 * lastMin;

    lv_img_set_angle (hfd->minShadow, min);
    lv_img_set_angle (hfd->minHand, min);

    lv_img_set_angle (hfd->hourShadow, hour);
    lv_img_set_angle (hfd->hourHand, hour);
  }

  lv_img_set_angle (hfd->secShadow, sec);
  lv_img_set_angle (hfd->secHand, sec);
}

static int onEntryHomerFace (int idx)
{
  HomerFaceData_t *hfd = (HomerFaceData_t *)(tileDesc[idx].data);

  log_d ("idx=%d", idx);

  screenTimeout = defaultScreenTimeout = DEFAULT_SCREEN_TIMEOUT * 5;
  defaultCpuFrequency = CPU_FREQ_MAX;
  setCpuFrequencyMhz (defaultCpuFrequency);

  if (hfd->timeTask == nullptr)
  {
    hfd->timeTask = lv_task_create (lv_update_task, 1000, LV_TASK_PRIO_LOWEST, (void *)idx);
  }
}

static int onExitHomerFace (int idx)
{
  HomerFaceData_t *hfd = (HomerFaceData_t *)(tileDesc[idx].data);

  log_d ("idx=%d", idx);

  if (hfd->timeTask != nullptr)
  {
    lv_task_del (hfd->timeTask);
    hfd->timeTask = nullptr;
  }
  
  screenTimeout = defaultScreenTimeout = DEFAULT_SCREEN_TIMEOUT;
  defaultCpuFrequency = CPU_FREQ_NORM;
}

static int createHomerFace (int idx)
{
  lv_obj_t *parentObj = tileDesc[idx].tile;
  lv_obj_t *canvas = lv_canvas_create (parentObj, NULL);
  lv_color_t *cbuf = (lv_color_t *)ps_malloc(LV_CANVAS_BUF_SIZE_TRUE_COLOR_ALPHA(240, 240) * sizeof (lv_color_t));

  memcpy (cbuf, homerFace.data, homerFace.data_size);
  
  lv_canvas_set_buffer (canvas, cbuf, 240, 240, LV_IMG_CF_TRUE_COLOR_ALPHA);
  
  lv_draw_line_dsc_t ticks;
  lv_draw_line_dsc_init (&ticks);
  ticks.opa = LV_OPA_100;
  ticks.color = LV_COLOR_WHITE;

  lv_point_t line[2];
  
  for (int i = 0; i < 60; i++)
  {
    int bot;
    float sx = cos(((i * 6) - 90) * 0.0174532925);
    float sy = sin(((i * 6) - 90) * 0.0174532925);
    
    line[0].x = sx * 117 + 120;
    line[0].y = sy * 117 + 120;

    if ((i % 15) == 0)
    {
      bot = 97;
      ticks.width = 6;
    }
    else if ((i % 5) == 0)
    {
      bot = 107;
      ticks.width = 4;
    }
    else
    {
      bot = 112;
      ticks.width = 2;
    }
    
    line[1].x = sx * bot + 120;
    line[1].y = sy * bot + 120;
    
    lv_canvas_draw_line (canvas, line, 2, &ticks);
  }
  
  lv_obj_align (canvas, parentObj, LV_ALIGN_CENTER, 0, 0);

  lv_obj_set_event_cb (parentObj, watchFaceEvent_cb);

  tileDesc[idx].onEntry  = onEntryHomerFace;
  tileDesc[idx].onExit   = onExitHomerFace;
  tileDesc[idx].onUpdate = updateHomerFace;

  tileDesc[idx].data = malloc (sizeof (HomerFaceData_t));

  HomerFaceData_t *hfd = (HomerFaceData_t *)(tileDesc[idx].data);

  hfd->leftEye = lv_img_create (parentObj, NULL);
  hfd->rightEye = lv_img_create (parentObj, NULL);

  hfd->minShadow  = lv_img_create (parentObj, NULL);
  hfd->minHand  = lv_img_create (parentObj, NULL);

  hfd->hourShadow = lv_img_create (parentObj, NULL);
  hfd->hourHand = lv_img_create (parentObj, NULL);

  hfd->secShadow  = lv_img_create (parentObj, NULL);
  hfd->secHand  = lv_img_create (parentObj, NULL);

  lv_img_set_src (hfd->leftEye, &eye);
  lv_img_set_src (hfd->rightEye, &eye);

  lv_img_set_src (hfd->hourShadow, &hourHand); lv_img_set_pivot (hfd->hourShadow, 7,  77);
  lv_img_set_src (hfd->minShadow,  &minHand);  lv_img_set_pivot (hfd->minShadow,  7, 105);
  lv_img_set_src (hfd->secShadow,  &secHand);  lv_img_set_pivot (hfd->secShadow, 22, 90);

  lv_img_set_src (hfd->hourHand, &hourHand); lv_img_set_pivot (hfd->hourHand, 7,  77);
  lv_img_set_src (hfd->minHand,  &minHand);  lv_img_set_pivot (hfd->minHand,  7, 105);
  lv_img_set_src (hfd->secHand,  &secHand);  lv_img_set_pivot (hfd->secHand, 22, 90);

  lv_obj_align (hfd->leftEye, parentObj, LV_ALIGN_CENTER, -30, -28);
  lv_obj_align (hfd->rightEye, parentObj, LV_ALIGN_CENTER, 30, -28);

  lv_obj_align (hfd->hourShadow, parentObj, LV_ALIGN_CENTER, 0, -32);
  lv_obj_align (hfd->minShadow,  parentObj, LV_ALIGN_CENTER, 0, -41);
  lv_obj_align (hfd->secShadow,  parentObj, LV_ALIGN_CENTER, 3, -15);

  lv_obj_align (hfd->hourHand, parentObj, LV_ALIGN_CENTER, 1, -40);
  lv_obj_align (hfd->minHand,  parentObj, LV_ALIGN_CENTER, 1, -49);
  lv_obj_align (hfd->secHand,  parentObj, LV_ALIGN_CENTER, 4, -26);

  static lv_style_t shadowStyle;

  lv_style_init (&shadowStyle);
  lv_style_set_radius (&shadowStyle, LV_OBJ_PART_MAIN, 0);
  lv_style_set_image_recolor (&shadowStyle, LV_STATE_DEFAULT, LV_COLOR_BLACK);
  lv_style_set_image_recolor_opa (&shadowStyle, LV_STATE_DEFAULT, LV_OPA_100);
  lv_style_set_image_opa (&shadowStyle, LV_STATE_DEFAULT, 63);  // LV_OPA_25ish!
  lv_style_set_border_width (&shadowStyle, LV_OBJ_PART_MAIN, 0);

  lv_obj_add_style (hfd->hourShadow, LV_IMG_PART_MAIN, &shadowStyle);
  lv_obj_add_style (hfd->minShadow, LV_IMG_PART_MAIN, &shadowStyle);
  lv_obj_add_style (hfd->secShadow, LV_IMG_PART_MAIN, &shadowStyle);

  hfd->timeTask = nullptr;

  updateHomerFace (idx);
}

/*****************************************************************
 *
 *          ! Keyboard Class
 *
 */

class Keyboard
{
public:
    typedef enum {
        KB_EVENT_OK,
        KB_EVENT_EXIT,
    } kb_event_t;

    typedef void (*kb_event_cb)(kb_event_t event);

    Keyboard()
    {
        _kbCont = nullptr;
    };

    ~Keyboard()
    {
        if (_kbCont)
            lv_obj_del(_kbCont);
        _kbCont = nullptr;
    };

    void create(lv_obj_t *parent =  nullptr)
    {
        static lv_style_t kbStyle;

	int height = LV_VER_RES;

	log_d ("parent=%p", parent);

        lv_style_init(&kbStyle);
        lv_style_set_radius(&kbStyle, LV_OBJ_PART_MAIN, 0);
        lv_style_set_bg_color(&kbStyle, LV_OBJ_PART_MAIN, LV_COLOR_GRAY);
        lv_style_set_bg_opa(&kbStyle, LV_OBJ_PART_MAIN, LV_OPA_0);
        lv_style_set_border_width(&kbStyle, LV_OBJ_PART_MAIN, 0);
        lv_style_set_text_color(&kbStyle, LV_OBJ_PART_MAIN, LV_COLOR_WHITE);
        lv_style_set_image_recolor(&kbStyle, LV_OBJ_PART_MAIN, LV_COLOR_WHITE);

        if (parent == nullptr) {
            parent = lv_scr_act();
        }

        _kbCont = lv_cont_create(parent, NULL);
        lv_obj_set_size(_kbCont, LV_HOR_RES, height);
        lv_obj_set_pos(_kbCont, 0, 30);
        lv_obj_add_style(_kbCont, LV_OBJ_PART_MAIN, &kbStyle);


        _kbPage = lv_page_create(_kbCont, NULL);
        lv_page_set_scrlbar_mode(_kbPage, LV_SCROLLBAR_MODE_OFF);
        lv_obj_set_size (_kbPage, LV_HOR_RES, height - 20);
        lv_obj_set_pos(_kbPage, 0, 20);
        lv_page_set_scrl_width(_kbPage,480);
        lv_page_set_scrl_height(_kbPage,190);

        lv_obj_t *ta = lv_textarea_create(_kbCont, NULL);
        lv_obj_set_height(ta, 20);
        lv_obj_set_pos(ta, 0, 0);

        lv_textarea_set_one_line(ta, true);
        lv_textarea_set_pwd_mode(ta, false);
        lv_textarea_set_text(ta, "");

        lv_obj_t *kb = lv_keyboard_create(_kbPage, NULL);
        lv_obj_set_pos(ta, 0, 0);
        lv_obj_set_height(kb, height - 20);
        lv_obj_set_width(kb, 480);
        lv_obj_move_foreground (_kbCont);
	      lv_obj_set_pos (kb, 0, 0);

        lv_keyboard_set_textarea(kb, ta);

        lv_obj_add_style(kb, LV_OBJ_PART_MAIN, &kbStyle);
        lv_obj_set_x(lv_page_get_scrollable(_kbPage), 0);
        lv_obj_set_event_cb(kb, __kb_event_cb);

        _kb = this;
    }

    void align(const lv_obj_t *base, lv_align_t align, lv_coord_t x = 0, lv_coord_t y = 0)
    {
        lv_obj_set_pos (_kbCont, 0, 0);
	lv_obj_move_foreground (_kbCont);
    }

    static void __kb_event_cb(lv_obj_t *kb, lv_event_t event)
    {
        if (event != LV_EVENT_VALUE_CHANGED && event != LV_EVENT_LONG_PRESSED_REPEAT) return;
        lv_keyboard_ext_t *ext = (lv_keyboard_ext_t *)lv_obj_get_ext_attr(kb);
        const char *txt = lv_btnmatrix_get_active_btn_text(kb);
        if (txt == NULL) return;
        static int index = 0;
        if ((strcmp(txt, LV_SYMBOL_OK) == 0) || (strcmp(txt, "Enter") == 0) || (strcmp(txt, LV_SYMBOL_NEW_LINE) == 0)){
            strcpy(__buf, lv_textarea_get_text(ext->ta));
            if (_kb->_cb != nullptr) {
                _kb->_cb(KB_EVENT_OK);
            }
            return;
        } else if ((LV_EVENT_CANCEL == event) || (strcmp(txt, LV_SYMBOL_CLOSE) == 0)) {
            if (_kb->_cb != nullptr) {
                _kb->_cb(KB_EVENT_EXIT);
            }
            return;
        } else if (strcmp(txt, LV_SYMBOL_LEFT) == 0) {
            log_i("LV_SYMBOL_LEFT before=%d",lv_obj_get_x(lv_page_get_scrollable(_kb->_kbPage)));
            lv_page_scroll_hor(_kb->_kbPage, lv_obj_get_x(lv_page_get_scrollable(_kb->_kbPage)) - 240);
            delay(250);
            log_i ("LV_SYMBOL_LEFT after=%d", lv_obj_get_x(lv_page_get_scrollable(_kb->_kbPage)));
        } else if (strcmp(txt, LV_SYMBOL_RIGHT) == 0) {
            log_i("LV_SYMBOL_RIGHT before=%d", lv_obj_get_x(lv_page_get_scrollable(_kb->_kbPage)));
            lv_page_scroll_hor(_kb->_kbPage, lv_obj_get_x(lv_page_get_scrollable(_kb->_kbPage)) *-1);
            delay(250);
            log_i("LV_SYMBOL_RIGHT after=%d", lv_obj_get_x(lv_page_get_scrollable(_kb->_kbPage)));
        } else {
            lv_keyboard_def_event_cb(kb, event);
        }
    }

    void setKeyboardEvent(kb_event_cb cb)
    {
        _cb = cb;
    }

    const char *getText()
    {
        return (const char *)__buf;
    }

    void hidden(bool en = true)
    {
        lv_obj_set_hidden(_kbCont, en);
    }

private:
    lv_obj_t *_kbPage = nullptr;
    lv_obj_t *_kbCont = nullptr;
    kb_event_cb _cb = nullptr;
    static const char *btnm_mapplus[10][23];
    static Keyboard *_kb;
    static char __buf[128];
};

Keyboard *Keyboard::_kb = nullptr;
char Keyboard::__buf[128];

/*****************************************************************
 *
 *          ! Switch Class
 *
 */
class Switch
{
public:
    typedef struct {
        const char *name;
        void (*cb)(uint8_t, bool);
    } switch_cfg_t;

    typedef void (*exit_cb)();
    Switch()
    {
        _swCont = nullptr;
    }
    ~Switch()
    {
        if (_swCont)
            lv_obj_del(_swCont);
        _swCont = nullptr;
    }

    void create(switch_cfg_t *cfg, uint8_t count, exit_cb cb, lv_obj_t *parent = nullptr)
    {
        static lv_style_t swlStyle;
        lv_style_init(&swlStyle);
        lv_style_set_radius(&swlStyle, LV_OBJ_PART_MAIN, 0);
        lv_style_set_bg_color(&swlStyle, LV_OBJ_PART_MAIN, LV_COLOR_GRAY);
        lv_style_set_bg_opa(&swlStyle, LV_OBJ_PART_MAIN, LV_OPA_0);
        lv_style_set_border_width(&swlStyle, LV_OBJ_PART_MAIN, 0);
        lv_style_set_border_opa(&swlStyle, LV_OBJ_PART_MAIN, LV_OPA_50);
        lv_style_set_text_color(&swlStyle, LV_OBJ_PART_MAIN, LV_COLOR_WHITE);
        lv_style_set_image_recolor(&swlStyle, LV_OBJ_PART_MAIN, LV_COLOR_WHITE);

        if (parent == nullptr) {
            parent = lv_scr_act();

            _swCont = lv_cont_create(parent, NULL);
            lv_obj_set_size(_swCont, LV_HOR_RES, LV_VER_RES - 30);
            lv_obj_align(_swCont, NULL, LV_ALIGN_CENTER, 0, 0);
            lv_obj_add_style(_swCont, LV_OBJ_PART_MAIN, &swlStyle);
        }
        else
	    _swCont = parent;

        _exit_cb = cb;

        _count = count;
        _sw = new lv_obj_t *[count];
        _cfg = new switch_cfg_t [count];

        memcpy(_cfg, cfg, sizeof(switch_cfg_t) * count);

        lv_obj_t *prev = nullptr;
        for (int i = 0; i < count; i++) {
            lv_obj_t *la1 = lv_label_create(_swCont, NULL);
            lv_label_set_text(la1, cfg[i].name);
            i == 0 ? lv_obj_align(la1, NULL, LV_ALIGN_IN_TOP_LEFT, 30, 20) : lv_obj_align(la1, prev, LV_ALIGN_OUT_BOTTOM_MID, 0, 20);
            _sw[i] = lv_imgbtn_create(_swCont, NULL);
            lv_imgbtn_set_src(_sw[i], LV_BTN_STATE_RELEASED, &off);
            lv_imgbtn_set_src(_sw[i], LV_BTN_STATE_PRESSED, &off);
            lv_imgbtn_set_src(_sw[i], LV_BTN_STATE_CHECKED_RELEASED, &off);
            lv_imgbtn_set_src(_sw[i], LV_BTN_STATE_CHECKED_PRESSED, &off);
            lv_obj_set_click(_sw[i], true);
            lv_obj_align(_sw[i], la1, LV_ALIGN_OUT_RIGHT_MID, 80, 0);
            lv_obj_set_event_cb(_sw[i], __switch_event_cb);
            prev = la1;
        }

        _switch = this;
    }

    void align(const lv_obj_t *base, lv_align_t align, lv_coord_t x = 0, lv_coord_t y = 0)
    {
        lv_obj_align(_swCont, base, align, x, y);
    }

    void hidden(bool en = true)
    {
        lv_obj_set_hidden(_swCont, en);
    }

    static void __switch_event_cb(lv_obj_t *obj, lv_event_t event)
    {
        log_d ("obj=%p, event=%d: %s", obj, event, decodeEvent (event));

        if (event == LV_EVENT_SHORT_CLICKED) {
            for (int i = 0; i < _switch->_count ; i++) {
                lv_obj_t *sw = _switch->_sw[i];
                if (obj == sw) {
                    const void *src =  lv_imgbtn_get_src(sw, LV_BTN_STATE_RELEASED);
                    const void *dst = src == &off ? &on : &off;
                    bool en = src == &off;
                    lv_imgbtn_set_src(sw, LV_BTN_STATE_RELEASED, dst);
                    lv_imgbtn_set_src(sw, LV_BTN_STATE_PRESSED, dst);
                    lv_imgbtn_set_src(sw, LV_BTN_STATE_CHECKED_RELEASED, dst);
                    lv_imgbtn_set_src(sw, LV_BTN_STATE_CHECKED_PRESSED, dst);
                    if (_switch->_cfg[i].cb != nullptr) {
                        _switch->_cfg[i].cb(i, en);
                    }
                    return;
                }
            }
        }
    }

    void setStatus(uint8_t index, bool en)
    {
        if (index > _count)return;
        lv_obj_t *sw = _sw[index];
        const void *dst =  en ? &on : &off;
        lv_imgbtn_set_src(sw, LV_BTN_STATE_RELEASED, dst);
        lv_imgbtn_set_src(sw, LV_BTN_STATE_PRESSED, dst);
        lv_imgbtn_set_src(sw, LV_BTN_STATE_CHECKED_RELEASED, dst);
        lv_imgbtn_set_src(sw, LV_BTN_STATE_CHECKED_PRESSED, dst);
    }

private:
    static Switch *_switch;
    lv_obj_t *_swCont = nullptr;
    uint8_t _count;
    lv_obj_t **_sw = nullptr;
    switch_cfg_t *_cfg = nullptr;
    lv_obj_t *_exitBtn = nullptr;
    exit_cb _exit_cb = nullptr;
};

Switch *Switch::_switch = nullptr;


/*****************************************************************
 *
 *          ! Preload Class
 *
 */
class Preload
{
public:
    Preload()
    {
        _preloadCont = nullptr;
    }
    ~Preload()
    {
        if (_preloadCont == nullptr) return;
        lv_obj_del(_preloadCont);
        _preloadCont = nullptr;
    }
    void create(lv_obj_t *parent = nullptr)
    {
        log_d ("Preload parent=%p", parent);

        if (parent == nullptr) {
            parent = lv_scr_act();
        }
        if (_preloadCont == nullptr) {
            static lv_style_t plStyle;
            lv_style_init(&plStyle);
            lv_style_set_radius(&plStyle, LV_OBJ_PART_MAIN, 0);
            lv_style_set_bg_color(&plStyle, LV_OBJ_PART_MAIN, LV_COLOR_GRAY);
            lv_style_set_bg_opa(&plStyle, LV_OBJ_PART_MAIN, LV_OPA_0);
            lv_style_set_border_width(&plStyle, LV_OBJ_PART_MAIN, 0);
            lv_style_set_text_color(&plStyle, LV_OBJ_PART_MAIN, LV_COLOR_WHITE);
            lv_style_set_image_recolor(&plStyle, LV_OBJ_PART_MAIN, LV_COLOR_WHITE);


            static lv_style_t style;
            lv_style_init(&style);
            lv_style_set_radius(&style, LV_OBJ_PART_MAIN, 0);
            lv_style_set_bg_color(&style, LV_OBJ_PART_MAIN, LV_COLOR_GRAY);
            lv_style_set_bg_opa(&style, LV_OBJ_PART_MAIN, LV_OPA_0);
            lv_style_set_border_width(&style, LV_OBJ_PART_MAIN, 0);
            lv_style_set_text_color(&style, LV_OBJ_PART_MAIN, LV_COLOR_WHITE);
            lv_style_set_image_recolor(&style, LV_OBJ_PART_MAIN, LV_COLOR_WHITE);

            _preloadCont = lv_cont_create(parent, NULL);
            lv_obj_set_size(_preloadCont, LV_HOR_RES, LV_VER_RES - 30);
            lv_obj_align(_preloadCont, NULL, LV_ALIGN_OUT_BOTTOM_MID, 0, 0);
            lv_obj_add_style(_preloadCont, LV_OBJ_PART_MAIN, &plStyle);

            lv_obj_t *preload = lv_spinner_create(_preloadCont, NULL);
            lv_obj_set_size(preload, lv_obj_get_width(_preloadCont) / 2, lv_obj_get_height(_preloadCont) / 2);
            lv_obj_add_style(preload, LV_OBJ_PART_MAIN, &style);
            lv_obj_align(preload, _preloadCont, LV_ALIGN_CENTER, 0, 0);
        }
    }
    void align(const lv_obj_t *base, lv_align_t align, lv_coord_t x = 0, lv_coord_t y = 0)
    {
        lv_obj_move_foreground (_preloadCont);
        lv_obj_set_pos(_preloadCont, 0, 0);
    }

    void hidden(bool en = true)
    {
        lv_obj_set_hidden(_preloadCont, en);
    }

private:
    lv_obj_t *_preloadCont = nullptr;
};


/*****************************************************************
 *
 *          ! List Class
 *
 */

class List
{
public:
    typedef void(*list_event_cb)(const char *);
    List()
    {
    }
    ~List()
    {
        if (_listCont == nullptr) return;
        lv_obj_del(_listCont);
        _listCont = nullptr;
    }
    void create(lv_obj_t *parent = nullptr)
    {
        log_d ("List parent=%p", parent);

        if (parent == nullptr) {
            parent = lv_scr_act();
        }
        if (_listCont == nullptr) {
            static lv_style_t listStyle;
            lv_style_init(&listStyle);
            lv_style_set_radius(&listStyle, LV_OBJ_PART_MAIN, 0);
            lv_style_set_bg_color(&listStyle, LV_OBJ_PART_MAIN, LV_COLOR_GRAY);
            lv_style_set_bg_opa(&listStyle, LV_OBJ_PART_MAIN, LV_OPA_0);
            lv_style_set_border_width(&listStyle, LV_OBJ_PART_MAIN, 0);
            lv_style_set_text_color(&listStyle, LV_OBJ_PART_MAIN, LV_COLOR_WHITE);
            lv_style_set_image_recolor(&listStyle, LV_OBJ_PART_MAIN, LV_COLOR_WHITE);

            _listCont = lv_list_create(lv_scr_act(), NULL);
            lv_list_set_scrollbar_mode(_listCont, LV_SCROLLBAR_MODE_OFF);
            lv_obj_set_size(_listCont, LV_HOR_RES, LV_VER_RES - 30);
            lv_obj_add_style(_listCont, LV_OBJ_PART_MAIN, &listStyle);
            lv_obj_align(_listCont, NULL, LV_ALIGN_CENTER, 0, 0);
        }
        _list = this;
    }

    void add(const char *txt, void *imgsrc = (void *)LV_SYMBOL_WIFI)
    {
        lv_obj_t *btn = lv_list_add_btn(_listCont, imgsrc, txt);
        lv_obj_set_event_cb(btn, __list_event_cb);
    }

    void align(const lv_obj_t *base, lv_align_t align, lv_coord_t x = 0, lv_coord_t y = 0)
    {
        lv_obj_set_pos (_listCont, 0, 0);
        lv_obj_move_foreground (_listCont);
    }

    void hidden(bool en = true)
    {
        lv_obj_set_hidden(_listCont, en);
    }

    static void __list_event_cb(lv_obj_t *obj, lv_event_t event)
    {
        if (event == LV_EVENT_SHORT_CLICKED) {
            const char *txt = lv_list_get_btn_text(obj);
            if (_list->_cb != nullptr) {
                _list->_cb(txt);
            }
        }
    }
    void setListCb(list_event_cb cb)
    {
        _cb = cb;
    }
private:
    lv_obj_t *_listCont = nullptr;
    static List *_list ;
    list_event_cb _cb = nullptr;
};
List *List::_list = nullptr;

/*****************************************************************
 *
 *          ! Task Class
 *
 */
class Task
{
public:
    Task()
    {
        _handler = nullptr;
        _cb = nullptr;
    }
    ~Task()
    {
        if ( _handler == nullptr)return;
        Serial.println("Free Task Func");
        lv_task_del(_handler);
        _handler = nullptr;
        _cb = nullptr;
    }

    void create(lv_task_cb_t cb, uint32_t period = 1000, lv_task_prio_t prio = LV_TASK_PRIO_LOW)
    {
        _handler = lv_task_create(cb,  period,  prio, NULL);
    };

private:
    lv_task_t *_handler = nullptr;
    lv_task_cb_t _cb = nullptr;
};

/*****************************************************************
 *
 *          ! MesBox Class
 *
 */

class MBox
{
public:
    MBox()
    {
        _mbox = nullptr;
    }
    ~MBox()
    {
        if (_mbox == nullptr)return;
        lv_obj_del(_mbox);
        _mbox = nullptr;
    }

    void create(const char *text, lv_event_cb_t event_cb, const char **btns = nullptr, lv_obj_t *par = nullptr)
    {
        if (_mbox != nullptr)return;
        lv_obj_t *p = par == nullptr ? lv_scr_act() : par;
        _mbox = lv_msgbox_create(p, NULL);
        lv_msgbox_set_text(_mbox, text);
        if (btns == nullptr) {
            static const char *defBtns[] = {"Ok", ""};
            lv_msgbox_add_btns(_mbox, defBtns);
        } else {
            lv_msgbox_add_btns(_mbox, btns);
        }
        lv_obj_set_width(_mbox, LV_HOR_RES - 40);
        lv_obj_set_event_cb(_mbox, event_cb);
        lv_obj_align(_mbox, NULL, LV_ALIGN_CENTER, 0, 0);
    }

    void setData(void *data)
    {
        lv_obj_set_user_data(_mbox, data);
    }

    void *getData()
    {
        return lv_obj_get_user_data(_mbox);
    }

    void setBtn(const char **btns)
    {
        lv_msgbox_add_btns(_mbox, btns);
    }

private:
    lv_obj_t *_mbox = nullptr;
};

/*****************************************************************
 *
 *          ! GLOBAL VALUE
 *
 */
static Keyboard *kb = nullptr;
static Switch *sw = nullptr;
static Preload *pl = nullptr;
static List *list = nullptr;
static Task *task = nullptr;
static Ticker *gTicker = nullptr;
static MBox *mbox = nullptr;

static char ssid[64], password[64];

/*****************************************************************
 *
 *          !WIFI EVENT
 *
 */
void wifi_connect_status(bool result)
{
    log_d ("result=%d", result);

    if (gTicker != nullptr) {
        delete gTicker;
        gTicker = nullptr;
    }
    if (kb != nullptr) {
        delete kb;
        kb = nullptr;
    }
    if (pl != nullptr) {
        delete pl;
        pl = nullptr;
    }
    if (result) {
        bar.show(LV_STATUS_BAR_WIFI);
    } else {
        bar.hidden(LV_STATUS_BAR_WIFI);
    }
}


void wifi_kb_event_cb(Keyboard::kb_event_t event)
{
    log_d ("keyboardEvent=%d", event);

    if (event == 0) {
        kb->hidden();
        Serial.println(kb->getText());
        strlcpy(password, kb->getText(), sizeof(password));
        pl->hidden(false);
        WiFi.mode(WIFI_STA);
        WiFi.disconnect();
        WiFi.begin(ssid, password);
        gTicker = new Ticker;
        gTicker->once_ms(5 * 1000, []() {
            wifi_connect_status(false);
        });
    } else if (event == 1) {
        delete kb;
        delete pl;
        pl = nullptr;
        kb = nullptr;
    }
}

static void wifi_sync_mbox_cb(lv_task_t *t)
{
    static  struct tm timeinfo;
    bool ret = false;
    static int retry = 0;
    configTzTime(RTC_TIME_ZONE, "pool.ntp.org");

    log_d ("task=%0", t);

    while (1) {
        ret = getLocalTime(&timeinfo);
        if (!ret) {
            Serial.printf("get ntp fail,retry : %d \n", retry++);
        } else {
            //! del preload
            delete pl;
            pl = nullptr;

            char format[256];
            snprintf(format, sizeof(format), "Time acquisition is:%d-%d-%d/%d:%d:%d, Whether to synchronize?", timeinfo.tm_year + 1900, timeinfo.tm_mon + 1, timeinfo.tm_mday, timeinfo.tm_hour, timeinfo.tm_min, timeinfo.tm_sec);
            Serial.println(format);
            delete task;
            task = nullptr;

            //! mbox
            static const char *btns[] = {"Ok", "Cancel", ""};
            mbox = new MBox;
            mbox->create(format, [](lv_obj_t *obj, lv_event_t event) {
                if (event == LV_EVENT_VALUE_CHANGED) {
                    const char *txt =  lv_msgbox_get_active_btn_text(obj);
                    if (!strcmp(txt, "Ok")) {

                        //!sync to rtc
                        struct tm *info =  (struct tm *)mbox->getData();
                        Serial.printf("read use data = %d:%d:%d - %d:%d:%d \n", info->tm_year + 1900, info->tm_mon + 1, info->tm_mday, info->tm_hour, info->tm_min, info->tm_sec);

                        TTGOClass *ttgo = TTGOClass::getWatch();
                        ttgo->rtc->setDateTime(info->tm_year + 1900, info->tm_mon + 1, info->tm_mday, info->tm_hour, info->tm_min, info->tm_sec);
                    } else if (!strcmp(txt, "Cancel")) {
                        //!cancel
                        // Serial.println("Cancel press");
                    }
                    delete mbox;
                    mbox = nullptr;
                }
            });
            mbox->setBtn(btns);
            mbox->setData(&timeinfo);
            return;
        }
    }
}

void wifi_sw_event_cb(uint8_t index, bool en)
{
    log_d ("index=%d, en=%d", index, en);

    switch (index) {
    case 0:
        if (en) {
            defaultCpuFrequency = CPU_FREQ_MEDIUM;
            setCpuFrequencyMhz (defaultCpuFrequency);
            WiFi.begin();
        } else {
            WiFi.disconnect();
            bar.hidden(LV_STATUS_BAR_WIFI);
        }
        break;
    case 1:
      if (en)
      {
        pl = new Preload;
        pl->create();
        pl->align (lv_scr_act(), LV_ALIGN_OUT_BOTTOM_MID);
        WiFi.disconnect();
        WiFi.scanNetworks(true);
      }
        break;
    case 2:
      if (en)
      {
        if (!WiFi.isConnected()) {
            //TODO pop-up window
            Serial.println("WiFi is not connected");
            return;
        } else {
            if (task != nullptr) {
                Serial.println("task is running ...");
                return;
            }
            task = new Task;
            task->create(wifi_sync_mbox_cb);
            pl = new Preload;
            pl->create();
            pl->align (lv_scr_act(), LV_ALIGN_OUT_BOTTOM_MID);
         }
        }
        break;
    default:
        break;
    }
}

void wifi_list_cb(const char *txt)
{
    log_d ("txt=%s", txt);

    strlcpy(ssid, txt, sizeof(ssid));
    delete list;
    list = nullptr;
    kb = new Keyboard;
    kb->create();
    kb->align (lv_scr_act(), LV_ALIGN_OUT_BOTTOM_MID);
    kb->setKeyboardEvent(wifi_kb_event_cb);
}

void wifi_list_add(const char *ssid)
{
    if (list == nullptr) {
        pl->hidden();
        list = new List;
        list->create();
        list->align (lv_scr_act(), LV_ALIGN_OUT_BOTTOM_MID);
        list->setListCb(wifi_list_cb);
    }
    list->add(ssid);
}

int createRowTitle (lv_obj_t *parent, const lv_img_dsc_t *image, char *name)
{
  lv_obj_t *img = lv_img_create (parent, NULL);

  lv_img_set_src (img, image);

  lv_obj_align(img, parent, LV_ALIGN_CENTER, 0, 0);

  lv_obj_t *label = lv_label_create (parent, NULL);

  lv_label_set_text (label, name);

  lv_obj_align (label, img, LV_ALIGN_OUT_BOTTOM_MID, 0, 0);
}

int createAbout (int idx)
{
  lv_obj_t *parentObj = tileDesc[idx].tile;

  log_d ("idx=%d", idx);

  createRowTitle (parentObj, &modules, "About");
}

int createWiFi (int idx)
{
  lv_obj_t *parentObj = tileDesc[idx].tile;

  log_d ("idx=%d", idx);

  createRowTitle (parentObj, &wifi, "WiFi");
}

int createWiFiSwitches (int idx)
{
  lv_obj_t *parentObj = tileDesc[idx].tile;

  log_d ("idx=%d", idx);
    Switch::switch_cfg_t cfg[3] = {{"Switch", wifi_sw_event_cb}, {"Scan", wifi_sw_event_cb}, {"NTP Sync", wifi_sw_event_cb}};
    sw = new Switch;
    sw->create(cfg, 3,
	      nullptr,
        parentObj);
    sw->align(parentObj, LV_ALIGN_IN_TOP_MID);
    sw->setStatus(0, WiFi.isConnected());
}

/*****************************************************************
 *
 *          ! MBOX EVENT
 *
 */
static lv_obj_t *mbox1 = nullptr;

static void create_mbox(const char *txt, lv_event_cb_t event_cb)
{
    if (mbox1 != nullptr)return;
    static const char *btns[] = {"Ok", ""};
    mbox1 = lv_msgbox_create(lv_scr_act(), NULL);
    lv_msgbox_set_text(mbox1, txt);
    lv_msgbox_add_btns(mbox1, btns);
    lv_obj_set_width(mbox1, LV_HOR_RES - 40);
    lv_obj_set_event_cb(mbox1, event_cb);
    lv_obj_align(mbox1, NULL, LV_ALIGN_CENTER, 0, 0);
}

static void destory_mbox()
{
    if (pl != nullptr) {
        delete pl;
        pl = nullptr;
    }
    if (list != nullptr) {
        delete list;
        list = nullptr;
    }
    if (mbox1 != nullptr) {
        lv_obj_del(mbox1);
        mbox1 = nullptr;
    }
}

/*****************************************************************
 *
 *          About EVENT
 *
 * Need to develop a more generic widget container that combines List, Table and 
 * ButtonMatrix widgets - probably based upon the Switch and List classes in this
 * gui.cpp file.
 */

static lv_obj_t *about = nullptr;

static int onEntryAbout (int idx)
{
  lv_obj_t *parentObj = tileDesc[idx].tile;
  lv_obj_t *label = (lv_obj_t *)(tileDesc[idx].data);

  log_d ("idx=%d", idx);

  lv_label_set_text_fmt (label, "\nagoodWatch %s\n(C) copyright Alex Goodyear\n%s\n\nCPU speed=%dMHz\nFree mem=%d",
                         THIS_VERSION_STR, __DATE__, getCpuFrequencyMhz(), esp_get_free_heap_size());

  lv_obj_align (label, parentObj, LV_ALIGN_IN_TOP_MID, 0, 0);
}

int createAboutInfo (int idx)
{
  lv_obj_t *parentObj = tileDesc[idx].tile;
  lv_obj_t *label = lv_label_create (parentObj, NULL);

  log_d ("idx=%d", idx);

  lv_obj_add_style (label, LV_OBJ_PART_MAIN, &settingStyle);
  lv_obj_align (label, parentObj, LV_ALIGN_IN_TOP_MID, 0, 0);

  tileDesc[idx].data = (void *)label;
  tileDesc[idx].onEntry = onEntryAbout;
}
