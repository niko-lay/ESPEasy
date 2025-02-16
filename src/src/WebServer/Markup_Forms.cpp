#include "../WebServer/Markup_Forms.h"

#include "../WebServer/ESPEasy_WebServer.h"
#include "../WebServer/AccessControl.h"
#include "../WebServer/Markup.h"
#include "../WebServer/HTML_wrappers.h"

#include "../Globals/Settings.h"

#include "../Helpers/Hardware_GPIO.h"
#include "../Helpers/Numerical.h"
#include "../Helpers/StringConverter.h"
#include "../Helpers/StringGenerator_GPIO.h"

// ********************************************************************************
// Add a separator as row start
// ********************************************************************************
void addFormSeparator(int clspan)
{
  addHtml(strformat(
    F("<TR><TD colspan='%d'><hr>"),
    clspan));
}

// ********************************************************************************
// Add a note as row start
// ********************************************************************************
void addFormNote(const __FlashStringHelper * text)
{
  addRowLabel_tr_id(EMPTY_STRING, EMPTY_STRING);
  addHtml(F(" <div class='note'>Note: "));
  addHtml(text);
  addHtml(F("</div>"));
}

void addFormNote(const String& text, const String& id)
{
  if (text.isEmpty())  return;
  addRowLabel_tr_id(EMPTY_STRING, id);
  addHtmlDiv(F("note"), concat(F("Note: "), text));
}

void addFormNote(const LabelType::Enum& label)
{
  addUnit(getFormUnit(label));
  addFormNote(getFormNote(label));
}

// ********************************************************************************
// Create Forms
// ********************************************************************************


// ********************************************************************************
// Add a checkbox Form
// ********************************************************************************

void addFormCheckBox_disabled(const String& label, const String& id, bool checked
                              #if FEATURE_TOOLTIPS
                              , const String& tooltip
                              #endif // if FEATURE_TOOLTIPS
                              ) {
  addFormCheckBox(label, id, checked, true
                  #if FEATURE_TOOLTIPS
                  , tooltip
                  #endif // if FEATURE_TOOLTIPS
                  );
}

void addFormCheckBox(const __FlashStringHelper * label, const __FlashStringHelper * id, bool checked, bool disabled)
{
  addRowLabel_tr_id(label, id);
  addCheckBox(id, checked, disabled);
}

void addFormCheckBox(const __FlashStringHelper * label, const String& id, bool checked, bool disabled)
{
  addRowLabel_tr_id(label, id);
  addCheckBox(id, checked, disabled);
}

void addFormCheckBox(const String& label, const String& id, bool checked, bool disabled
                     #if FEATURE_TOOLTIPS
                     , const String& tooltip
                     #endif // if FEATURE_TOOLTIPS
                     )
{
  addRowLabel_tr_id(label, id);
  addCheckBox(id, checked, disabled
              #if FEATURE_TOOLTIPS
              , tooltip
              #endif // if FEATURE_TOOLTIPS
              );
}

void addFormCheckBox(LabelType::Enum label, bool checked, bool disabled
                     #if FEATURE_TOOLTIPS
                     , const String& tooltip
                     #endif // if FEATURE_TOOLTIPS
                     ) {
  addFormCheckBox(getLabel(label), getInternalLabel(label), checked, disabled
                  #if FEATURE_TOOLTIPS
                  , tooltip
                  #endif // if FEATURE_TOOLTIPS
                  );
  addFormNote(label);
}

void addFormCheckBox_disabled(LabelType::Enum label, bool checked) {
  addFormCheckBox(label, checked, true);
}

// ********************************************************************************
// Add a Numeric Box form
// ********************************************************************************
void addFormNumericBox(LabelType::Enum label, int value, int min, int max
                       #if FEATURE_TOOLTIPS
                       , const String& tooltip
                       #endif // if FEATURE_TOOLTIPS
                       , bool disabled
                       )
{
  addFormNumericBox(getLabel(label), getInternalLabel(label), value, min, max
                    #if FEATURE_TOOLTIPS
                    , tooltip
                    #endif // if FEATURE_TOOLTIPS
                    , disabled
                    );
  addFormNote(label);
}

void addFormNumericBox(const __FlashStringHelper * label, 
                       const __FlashStringHelper * id, 
                       int value, 
                       int min, 
                       int max
                       #if FEATURE_TOOLTIPS
                       ,
                       const String& tooltip
                       #endif // if FEATURE_TOOLTIPS
                       ,
                       bool disabled
                       )
{
  addFormNumericBox(String(label), String(id), value, min, max
                    #if FEATURE_TOOLTIPS
                    , tooltip
                    #endif // if FEATURE_TOOLTIPS
                    , disabled
                    );

}

void addFormNumericBox(const String& label, const String& id, int value, int min, int max
                       #if FEATURE_TOOLTIPS
                       , const String& tooltip
                       #endif // if FEATURE_TOOLTIPS
                       , bool disabled
                       )
{
  addRowLabel_tr_id(label, id);
  addNumericBox(id, value, min, max
                #if FEATURE_TOOLTIPS
                , F("widenumber"), tooltip
                #endif // if FEATURE_TOOLTIPS
                , disabled
                );
}

void addFormFloatNumberBox(LabelType::Enum label, float value, float min, float max, uint8_t nrDecimals, float stepsize
                           #if FEATURE_TOOLTIPS
                           , const String& tooltip
                           #endif // if FEATURE_TOOLTIPS
                           ) {
  addFormFloatNumberBox(getLabel(label), getInternalLabel(label), value, min, max, nrDecimals, stepsize
                        #if FEATURE_TOOLTIPS
                        , tooltip
                        #endif // if FEATURE_TOOLTIPS
                        );
  addFormNote(label);
}

void addFormFloatNumberBox(const String& label,
                           const String& id,
                           float         value,
                           float         min,
                           float         max,
                           uint8_t       nrDecimals,
                           float         stepsize
                           #if FEATURE_TOOLTIPS
                           ,
                           const String& tooltip
                           #endif // if FEATURE_TOOLTIPS
                           )
{
  addRowLabel_tr_id(label, id);
  addFloatNumberBox(id, value, min, max, nrDecimals, stepsize
                    #if FEATURE_TOOLTIPS
                    , tooltip
                    #endif // if FEATURE_TOOLTIPS
                    );
}

void addFormFloatNumberBox(const __FlashStringHelper * label,
                           const __FlashStringHelper * id,
                           float         value,
                           float         min,
                           float         max,
                           uint8_t       nrDecimals,
                           float         stepsize
                           #if FEATURE_TOOLTIPS
                           ,
                           const String& tooltip
                           #endif // if FEATURE_TOOLTIPS
                           )
{
  addRowLabel_tr_id(label, id);
  addFloatNumberBox(id, value, min, max, nrDecimals, stepsize
                    #if FEATURE_TOOLTIPS
                    , tooltip
                    #endif // if FEATURE_TOOLTIPS
                    );
}



// ********************************************************************************
// Add a task selector form
// ********************************************************************************
void addTaskSelectBox(const String& label, const String& id, taskIndex_t choice)
{
  addRowLabel_tr_id(label, id);
  addTaskSelect(id, choice);
}

// ********************************************************************************
// Add a Text Box form
// ********************************************************************************
void addFormTextBox(const __FlashStringHelper * label,
                    const __FlashStringHelper * id,
                    const String& value,
                    int           maxlength,
                    bool          readonly,
                    bool          required,
                    const String& pattern)
{
  addRowLabel_tr_id(label, id);
  addTextBox(id, value, maxlength, readonly, required, pattern);
}

void addFormTextBox(const String  & label,
                    const String  & id,
                    const String  & value,
                    int             maxlength,
                    bool            readonly,
                    bool            required,
                    const String& pattern
                    #if FEATURE_TOOLTIPS
                    , const String& tooltip
                    #endif // if FEATURE_TOOLTIPS
                    ,
                    const String&   datalist
                    )
{
  addRowLabel_tr_id(label, id);
  addTextBox(id, value, maxlength, readonly, required, pattern, F("wide")
             #if FEATURE_TOOLTIPS
             , tooltip
             #endif // if FEATURE_TOOLTIPS
             , datalist
             );
}

void addFormTextBox(const __FlashStringHelper * classname,
                    const String& label,
                    const String& id,
                    const String& value,                    
                    int           maxlength,
                    bool          readonly ,
                    bool          required ,
                    const String& pattern  
                    #if FEATURE_TOOLTIPS
                    ,
                    const String& tooltip 
                    #endif // if FEATURE_TOOLTIPS
                    ,
                    const String& datalist
                    )
{
  addRowLabel_tr_id(label, id);
  addTextBox(id, value, maxlength, readonly, required, pattern, classname
             #if FEATURE_TOOLTIPS
             , tooltip
             #endif // if FEATURE_TOOLTIPS
             , datalist
             );
}



void addFormTextArea(const String  & label,
                     const String  & id,
                     const String  & value,
                     int             maxlength,
                     int             rows,
                     int             columns,
                     bool            readonly,
                     bool            required
                     #if FEATURE_TOOLTIPS
                     , const String& tooltip
                     #endif // if FEATURE_TOOLTIPS
                     )
{
  addRowLabel_tr_id(label, id);
  addTextArea(id, value, maxlength, rows, columns, readonly, required
              #if FEATURE_TOOLTIPS
              , tooltip
              #endif // if FEATURE_TOOLTIPS
              );
}

// ********************************************************************************
// Add a Password Box form
// ********************************************************************************

void addFormPasswordBox(const String& label, const String& id, const String& password, int maxlength
                        #if FEATURE_TOOLTIPS
                        , const String& tooltip
                        #endif // if FEATURE_TOOLTIPS
                        )
{
  addRowLabel_tr_id(label, id);

  addHtml(F("<input "));
  addHtmlAttribute(F("class"),     F("wide"));
  addHtmlAttribute(F("type"),      F("password"));
  addHtmlAttribute(F("name"),      id);
  addHtmlAttribute(F("id"),        id);
  addHtmlAttribute(F("maxlength"), maxlength);

  #if FEATURE_TOOLTIPS

  if (tooltip.length() > 0) {
    addHtmlAttribute(F("title"), tooltip);
  }
  #endif // if FEATURE_TOOLTIPS
  addHtmlAttribute(F("value"), (password.length() == 0) ? F("") : F("*****"));
  addHtml('>');
}

bool getFormPassword(const String& id, String& password)
{
  password = webArg(id);
  /*
  if (loglevelActiveFor(LOG_LEVEL_DEBUG)) {
    addLog(LOG_LEVEL_DEBUG, concat(F("getFormPassword: "), password));
  } 
  */ 
  return !equals(password, F("*****"));
}

// ********************************************************************************
// Add a IP Box form
// ********************************************************************************
void addFormIPBox(const __FlashStringHelper *label,
                  const __FlashStringHelper *id,
                  const uint8_t ip[4])
{
  addFormIPBox(String(label), String(id), ip);
}

void addFormTextBox(const String& label, const String& id, const String& value)
{
  addRowLabel_tr_id(label, id);

  addHtml(strformat(
    F("<input class='wide' type='text' name='%s' id='%s' value='%s'>"),
    id.c_str(),
    id.c_str(),
    value.c_str()
  ));
}

void addFormIPBox(const String& label, const String& id, const uint8_t ip[4])
{
  const bool empty_IP = (ip[0] == 0 && ip[1] == 0 && ip[2] == 0 && ip[3] == 0);

  addFormTextBox(label, id, (empty_IP) ? EMPTY_STRING : formatIP(ip));
}

// ********************************************************************************
// Add a MAC Box form
// ********************************************************************************
void addFormMACBox(const String& label, const String& id, const MAC_address mac)
{
  addFormTextBox(
    label, 
    id, 
    mac.all_zero() ? EMPTY_STRING.c_str() : mac.toString());
}

// ********************************************************************************
// Add a IP Access Control select dropdown list
// ********************************************************************************
void addFormIPaccessControlSelect(const __FlashStringHelper * label, const __FlashStringHelper * id, int choice)
{
  addRowLabel_tr_id(label, id);
  addIPaccessControlSelect(id, choice);
}

// ********************************************************************************
// a Separator character selector
// ********************************************************************************
void addFormSeparatorCharInput(const __FlashStringHelper *rowLabel,
                               const __FlashStringHelper *id,
                               int                        value,
                               const String             & charset,
                               const __FlashStringHelper *additionalText) {
  const int len = charset.length() + 1;
  String    charList[len];
  int charOpts[len];

  charList[0] = F("None");
  charOpts[0] = 0;

  for (uint16_t i = 0; i < charset.length(); i++) {
    charList[i + 1] = charset[i];
    charOpts[i + 1] = static_cast<int>(charset[i]);
  }
  addFormSelector(rowLabel, id, len, charList, charOpts, value);

  if (!String(additionalText).isEmpty()) {
    addUnit(additionalText);
  }
}

// ********************************************************************************
// Add a selector form
// ********************************************************************************
void addFormPinSelect(PinSelectPurpose purpose, const String& label, const __FlashStringHelper * id, int choice)
{
  addRowLabel_tr_id(label, id);
  addPinSelect(purpose, id, choice);
}

void addFormPinSelect(PinSelectPurpose purpose, const __FlashStringHelper * label, const __FlashStringHelper * id, int choice)
{
  addRowLabel_tr_id(label, id);
  addPinSelect(purpose, id, choice);
}

/*
void addFormPinSelect(const String& label, const __FlashStringHelper * id, int choice)
{
  addRowLabel_tr_id(label, id);
  addPinSelect(PinSelectPurpose::Generic, id, choice);
}

void addFormPinSelect(const __FlashStringHelper * label,
                      const __FlashStringHelper * id,
                      int           choice)
{
  addRowLabel_tr_id(label, id);
  addPinSelect(PinSelectPurpose::Generic, id, choice);
}

void addFormPinSelect(const String& label, const String & id, int choice)
{
  addRowLabel_tr_id(label, id);
  addPinSelect(PinSelectPurpose::Generic, id, choice);
}
*/

void addFormPinSelectI2C(const String& label, const String& id, int choice)
{
  addRowLabel_tr_id(label, id);
  addPinSelect(PinSelectPurpose::I2C, id, choice);
}

void addFormSelectorI2C(const String& id,
                        int           addressCount,
                        const uint8_t addresses[],
                        int           selectedIndex,
                        uint8_t       defaultAddress
                        #if FEATURE_TOOLTIPS
                        , const String& tooltip
                        #endif // if FEATURE_TOOLTIPS
                        )
{
  addRowLabel_tr_id(F("I2C Address"), id);
  do_addSelector_Head(id, F(""), EMPTY_STRING, false
                      #if FEATURE_TOOLTIPS
                      , tooltip
                      #endif // if FEATURE_TOOLTIPS
                      );

  for (int x = 0; x < addressCount; x++)
  {
    String option = formatToHex_decimal(addresses[x]);

    if (((x == 0) && (defaultAddress == 0)) || (defaultAddress == addresses[x])) {
      option += F(" - (default)");
    }
    addSelector_Item(option, addresses[x], addresses[x] == selectedIndex);
  }
  addSelector_Foot();
}

void addFormSelector(const __FlashStringHelper * label, const __FlashStringHelper * id, int optionCount, const __FlashStringHelper * options[], const int indices[], int selectedIndex, bool reloadonchange)
{
  addFormSelector(String(label), String(id), optionCount, options, indices, nullptr, selectedIndex, reloadonchange);
}

void addFormSelector(const __FlashStringHelper * label, const String& id, int optionCount, const __FlashStringHelper * options[], const int indices[], int selectedIndex, bool reloadonchange)
{
  addFormSelector(String(label), id, optionCount, options, indices, nullptr, selectedIndex, reloadonchange);
}

void addFormSelector(const String& label, const String& id, int optionCount, const __FlashStringHelper * options[], const int indices[], int selectedIndex)
{
  addFormSelector(label, id, optionCount, options, indices, nullptr, selectedIndex, false);
}

void addFormSelector(const __FlashStringHelper * label, const __FlashStringHelper * id, int optionCount, const String options[], const int indices[], int selectedIndex)
{
  addFormSelector(String(label), String(id), optionCount, options, indices, nullptr, selectedIndex, false);
}

void addFormSelector(const String  & label,
                     const String  & id,
                     int             optionCount,
                     const String    options[],
                     const int       indices[],
                     int           selectedIndex
                     #if FEATURE_TOOLTIPS
                     , const String& tooltip
                     #endif // if FEATURE_TOOLTIPS
                     )
{
  addFormSelector(label, id, optionCount, options, indices, nullptr, selectedIndex, false
                  #if FEATURE_TOOLTIPS
                  , tooltip
                  #endif // if FEATURE_TOOLTIPS
                  );
}

void addFormSelector(const String& label,
                     const String& id,
                     int           optionCount,
                     const __FlashStringHelper * options[],
                     const int     indices[],
                     int           selectedIndex,
                     bool          reloadonchange)
{
  addFormSelector(label, id, optionCount, options, indices, nullptr, selectedIndex, reloadonchange);
}

void addFormSelector(const String& label,
                     const String& id,
                     int           optionCount,
                     const __FlashStringHelper * options[],
                     const int     indices[],
                     const String  attr[],
                     int           selectedIndex,
                     bool          reloadonchange)
{
  addRowLabel_tr_id(label, id);
  addSelector(id, optionCount, options, indices, attr, selectedIndex, reloadonchange, true);
}

void addFormSelector(const String& label,
                     const String& id,
                     int           optionCount,
                     const String  options[],
                     const int     indices[],
                     int           selectedIndex,
                     bool          reloadonchange
                     #if FEATURE_TOOLTIPS
                     , const String& tooltip
                     #endif // if FEATURE_TOOLTIPS
                    )
{
  addFormSelector(label, id, optionCount, options, indices, nullptr, selectedIndex, reloadonchange
                  #if FEATURE_TOOLTIPS
                  , tooltip
                  #endif // if FEATURE_TOOLTIPS
                 );
}

void addFormSelector(const String  & label,
                     const String  & id,
                     int             optionCount,
                     const String    options[],
                     const int       indices[],
                     const String    attr[],
                     int             selectedIndex,
                     bool       reloadonchange
                     #if FEATURE_TOOLTIPS
                     , const String& tooltip
                     #endif // if FEATURE_TOOLTIPS
                     )
{
  addRowLabel_tr_id(label, id);
  addSelector(id, optionCount, options, indices, attr, selectedIndex, reloadonchange, true, F("wide")
              #if FEATURE_TOOLTIPS
              , tooltip
              #endif // if FEATURE_TOOLTIPS
              );
}

void addFormSelector_script(const __FlashStringHelper * label,
                            const __FlashStringHelper * id,
                            int           optionCount,
                            const __FlashStringHelper * options[],
                            const int     indices[],
                            const String  attr[],
                            int           selectedIndex,
                            const __FlashStringHelper * onChangeCall
                            #if FEATURE_TOOLTIPS
                            , const String& tooltip
                            #endif // if FEATURE_TOOLTIPS
                            )
{
  addRowLabel_tr_id(label, id);
  do_addSelector_Head(id, F("wide"), onChangeCall, false
                      #if FEATURE_TOOLTIPS
                      , tooltip
                      #endif // if FEATURE_TOOLTIPS
                      );
  addSelector_options(optionCount, options, indices, attr, selectedIndex);
  addSelector_Foot();
}

void addFormSelector_script(const __FlashStringHelper * label,
                            const __FlashStringHelper * id,
                            int             optionCount,
                            const String    options[],
                            const int       indices[],
                            const String    attr[],
                            int             selectedIndex,
                            const __FlashStringHelper * onChangeCall
                            #if FEATURE_TOOLTIPS
                            , const String& tooltip
                            #endif // if FEATURE_TOOLTIPS
                            )
{
  addRowLabel_tr_id(label, id);
  do_addSelector_Head(id, F("wide"), onChangeCall, false
                      #if FEATURE_TOOLTIPS
                      , tooltip
                      #endif // if FEATURE_TOOLTIPS
                      );
  addSelector_options(optionCount, options, indices, attr, selectedIndex);
  addSelector_Foot();
}

void addFormSelector_YesNo(const __FlashStringHelper * label,
                           const __FlashStringHelper * id,
                           int           selectedIndex,
                           bool       reloadonchange)
{
  addFormSelector_YesNo(label, String(id), selectedIndex, reloadonchange);
}

void addFormSelector_YesNo(const __FlashStringHelper * label,
                           const String& id,
                           int           selectedIndex,
                           bool       reloadonchange)
{
  const __FlashStringHelper *optionsNoYes[] = { F("No"), F("Yes") };
  int optionValuesNoYes[]                   = { 0, 1 };
  addFormSelector(label, id, NR_ELEMENTS(optionValuesNoYes), optionsNoYes, optionValuesNoYes, selectedIndex, reloadonchange);
}



// ********************************************************************************
// Add a GPIO pin select dropdown list
// ********************************************************************************
void addFormPinStateSelect(int gpio, int choice)
{
  bool enabled = true;

  if (isSerialConsolePin(gpio)) {
    // do not add the pin state select for these pins.
    enabled = false;
  }
  if (Settings.isEthernetPin(gpio)) {
    // do not add the pin state select for non-optional Ethernet pins
    enabled = false;
  }
  int  pinnr = -1;
  bool input, output, warning;

  if (getGpioInfo(gpio, pinnr, input, output, warning)) {
    const String id = String('p') + gpio;
    addRowLabel_tr_id(
      concat(
        F("Pin mode "), 
        createGPIO_label(gpio, pinnr, input, output, warning)), 
      id);
    bool hasPullUp, hasPullDown;
    getGpioPullResistor(gpio, hasPullUp, hasPullDown);
    int nr_options = 0;
    const __FlashStringHelper * options[6];
    int    option_val[6];
    options[nr_options]    = F("Default");
    option_val[nr_options] = static_cast<int>(PinBootState::Default_state);
    ++nr_options;

    if (output) {
      options[nr_options]    = F("Output Low");
      option_val[nr_options] = static_cast<int>(PinBootState::Output_low);
      ++nr_options;
      options[nr_options]    = F("Output High");
      option_val[nr_options] = static_cast<int>(PinBootState::Output_high);
      ++nr_options;
    }

    if (input) {
      if (hasPullUp) {
        options[nr_options]    = F("Input pullup");
        option_val[nr_options] = static_cast<int>(PinBootState::Input_pullup);
        ++nr_options;
      }

      if (hasPullDown) {
        options[nr_options]    = F("Input pulldown");
        option_val[nr_options] = static_cast<int>(PinBootState::Input_pulldown);
        ++nr_options;
      }

      if (!hasPullUp && !hasPullDown) {
        options[nr_options]    = F("Input");
        option_val[nr_options] = static_cast<int>(PinBootState::Input);
        ++nr_options;
      }
    }
    addSelector(id, nr_options, options, option_val, nullptr, choice, false, enabled);
    {
      const String conflict = getConflictingUse(gpio);
      if (!conflict.isEmpty()) {
        addUnit(conflict);
      }
    }
  }
}

// ********************************************************************************
// Retrieve return values from form/checkbox.
// ********************************************************************************
int getFormItemInt(const __FlashStringHelper * key, int defaultValue) {
  return getFormItemInt(String(key), defaultValue);
}

int getFormItemInt(const String& key, int defaultValue) {
  int value = defaultValue;

  getCheckWebserverArg_int(key, value);
  return value;
}

bool getCheckWebserverArg_int(const String& key, int& value) {
  const String valueStr = webArg(key);
  if (valueStr.isEmpty()) return false;
  // FIXME TD-er: Since ESP_IDF 5.1 int32_t != int
  int32_t tmp{};
  const bool res = validIntFromString(valueStr, tmp);
  value = tmp;
  return res;
}

bool update_whenset_FormItemInt(const __FlashStringHelper * key,
                                int         & value) 
{
  return update_whenset_FormItemInt(String(key), value);
}

bool update_whenset_FormItemInt(const String& key, int& value) {
  int tmpVal;

  if (getCheckWebserverArg_int(key, tmpVal)) {
    value = tmpVal;
    return true;
  }
  return false;
}

bool update_whenset_FormItemInt(const __FlashStringHelper * key,
                                uint8_t& value) 
{
  return update_whenset_FormItemInt(String(key), value);
}


bool update_whenset_FormItemInt(const String& key, uint8_t& value) {
  int tmpVal;

  if (getCheckWebserverArg_int(key, tmpVal)) {
    value = tmpVal;
    return true;
  }
  return false;
}

// Note: Checkbox values will not appear in POST Form data if unchecked.
// So if webserver does not have an argument for a checkbox form, it means it should be considered unchecked.
bool isFormItemChecked(const __FlashStringHelper * id)
{
  return isFormItemChecked(String(id));
}

bool isFormItemChecked(const String& id)
{
  return equals(webArg(id), F("on"));
}

bool isFormItemChecked(const LabelType::Enum& id)
{
  return isFormItemChecked(getInternalLabel(id));
}

int getFormItemInt(const __FlashStringHelper * id)
{
  return getFormItemInt(String(id), 0);
}

int getFormItemInt(const String& id)
{
  return getFormItemInt(id, 0);
}

int getFormItemInt(const LabelType::Enum& id)
{
  return getFormItemInt(getInternalLabel(id), 0);
}

float getFormItemFloat(const __FlashStringHelper * id)
{
  return getFormItemFloat(String(id));
}

float getFormItemFloat(const String& id)
{
  const String val = webArg(id);
  float res = 0.0;
  if (val.length() > 0) {
    validFloatFromString(val, res);
  }
  return res;
}

float getFormItemFloat(const LabelType::Enum& id)
{
  return getFormItemFloat(getInternalLabel(id));
}

bool isFormItem(const String& id)
{
  return !webArg(id).isEmpty();
}

void copyFormPassword(const __FlashStringHelper * id, char *pPassword, int maxlength)
{
  String password;

  if (getFormPassword(id, password)) {
    safe_strncpy(pPassword, password.c_str(), maxlength);
  }
}
