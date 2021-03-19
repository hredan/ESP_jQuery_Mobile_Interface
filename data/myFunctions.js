'use strict';

var UiFunc = {
    handleFlipLed : function(){
        var checked = $( "#flipAlarm" ).prop("checked");        
        SleepUinoCom.setLed(checked)
    },
};