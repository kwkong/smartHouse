// function on()
// {
//   $.get("ESPsmartHouse.php", {"on":""})

//  // alert("On");
// }

// function off()
// {
//   $.get("ESPsmartHouse.php", {"off":""})

//   //alert("Off");
// }

function getValue() {
   var isChecked = document.getElementById("myCheckBox").checked;
    
   if(isChecked){ 
     alert("Input is checked");
   } else {
     alert("Input is NOT checked");
   }
}
