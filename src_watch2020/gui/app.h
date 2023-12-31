/****************************************************************************
 *   Sep 2 08:21:51 2020
 *   Copyright  2020  Dirk Brosswick
 *   Email: dirk.brosswick@googlemail.com
 ****************************************************************************/
 
/*
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
 */
#ifndef _APP_H
    #define _APP_H
    
    #include "gui/icon.h"
    /**
     * @brief core autocall type definition
     */
    typedef void ( * APP_AUTOCALL_FUNC ) ( void );
    /**
     * @brief callback table entry structure
     */
    typedef struct {
        APP_AUTOCALL_FUNC function;             /** @brief pointer to a callback function */
        size_t prio;                            /** @brief priority of the callback function */
    } app_autocall_table_t;
    /**
     * @brief autocall function for module setup
     * 
     * @param function          pointer to the module registration function
     * @param prio              priority of the module
     */
    int app_autocall_function( APP_AUTOCALL_FUNC function, size_t prio );
    void app_autocall_all_setup_functions( void );
    /**
     * @brief register an application icon
     * 
     * @param   appname     application name
     * @param   icon        pointer to an 64x64px icon
     * @param   event_cb    pointer to an callback function
     */
    icon_t *app_register( const char* appname, const lv_img_dsc_t *icon, lv_event_cb_t event_cb );
    /**
     * @brief   set the icon indicator
     * 
     * @param   app         pointer to an app_icon_t structure
     * @param   indicator   possible values are:    APP_ICON_INDICATOR_OK, APP_ICON_INDICATOR_FAIL, APP_ICON_INDICATOR_UPDATE ....
     */
    void app_set_indicator( icon_t *app, icon_indicator_t indicator );
    /**
     * @brief   hide the icon indicator
     * 
     * @param   app         pointer to an app_icon_t structure
     */
    void app_hide_indicator( icon_t *app );
    /**
     * @brief   set the application icon
     * 
     * @param   app         pointer to an app_icon_t structure
     * @param   icon        pointer to an 64x64px icon
     */
    void app_set_icon( icon_t *app, lv_obj_t *icon );
    /**
     * @brief   get the numbers of active app
     * 
     * @return  zero or the numbers of active apps
     */
    int32_t app_get_active_app_entrys( void );

#endif // _APP_H