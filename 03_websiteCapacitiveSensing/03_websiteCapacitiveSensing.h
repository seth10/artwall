static const char WEBPAGE_TEMPLATE[] PROGMEM = R"=====(
<h1 id="display" style="font-size: 800px">placeholder</h1>
<script>
function update() {
  var xhr = new XMLHttpRequest();
  xhr.open("GET", "/data", true);
  xhr.onload = function (e) {
    document.getElementById("display").innerHTML = xhr.responseText;
  };
  xhr.send(null);
}
setInterval(update, 250);
</script>
)=====";
