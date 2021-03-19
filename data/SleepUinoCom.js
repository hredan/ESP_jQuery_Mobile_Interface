'use strict';
var SleepUinoCom = {
    //needed for Mockup Communication (in case enableServerCom = false)
    enableServerCom : true,
    setLed : function (value){
        var jsonObj = {"led": value}
        if (this.enableServerCom)
        {
            
            $.ajax({url: "/setLed", type: "POST", dataType: "json", data: jsonObj})
            .success(function(result){
                console.log(result);
            });
        }
        else
        {
            console.log("FakeCom: setLed: " + JSON.stringify(jsonObj));
        }
    },
};