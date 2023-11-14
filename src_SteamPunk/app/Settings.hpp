//
//    LunokWatch, a open source smartwatch software
//    Copyright (C) 2022,2023  Jordi Rubió <jordi@binarycell.org>
//    This file is part of LunokWatch.
//
// LunokWatch is free software: you can redistribute it and/or modify it under
// the terms of the GNU General Public License as published by the Free Software 
// Foundation, either version 3 of the License, or (at your option) any later 
// version.
//
// LunokWatch is distributed in the hope that it will be useful, but WITHOUT 
// ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
// FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for more 
// details.
//
// You should have received a copy of the GNU General Public License along with 
// LunokWatch. If not, see <https://www.gnu.org/licenses/>. 
//

#ifndef __LUNOKIOT__SETTINGS_APP__
#define __LUNOKIOT__SETTINGS_APP__

#include "../UI/AppTemplate.hpp" // typical app design base with back button

// widgets used
#include "../UI/widgets/ButtonImageXBMWidget.hpp"
#include "../UI/widgets/SwitchWidget.hpp"

class SettingsApplication: public TemplateApplication {
    private:
        ButtonImageXBMWidget * btnHelp = nullptr;
        SwitchWidget * ntpCheck = nullptr;
        SwitchWidget * openweatherCheck = nullptr;
        SwitchWidget * wifiCheck = nullptr;
        SwitchWidget * bleCheck = nullptr;
        SwitchWidget * ntpBLECheck = nullptr;
    public:
        const char *AppName() override { return "Basic settings"; };
        SettingsApplication();
        virtual ~SettingsApplication();
        bool Tick();
};

#endif
