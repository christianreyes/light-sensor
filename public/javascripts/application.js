
$(function(){
  /*
  ============================
         SOCKET LOGIC
  ============================
  */
  
  // connect to server. use auto-discovery for port
  var socket = io.connect();
  
  setInterval(function(){
    socket.emit("get-level", null);
  }, 100);
  
  socket.on("current-level", function(data){
    $('.level').text(data.level);
    $('.bar').css("width", data.level * 100);
  });
  
});
  
