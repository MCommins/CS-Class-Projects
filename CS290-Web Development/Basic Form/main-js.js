function verifyUsingJS() {
  var areaCodePattern=/^[0-9]{3}$/;
  var areaCode=document.getElementsByName("area_code")[0].value;
  if(areaCodePattern.test(areaCode)) alert("Good!");
  else alert("You don't know what an area code is? Really!?");
