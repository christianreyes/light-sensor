
/**
 * Module dependencies.
 */

var SerialPort = require("serialport").SerialPort
var serialPort = new SerialPort("/dev/tty.usbserial-A100OSY8");

var express = require('express')
  , routes = require('./routes')

var app = module.exports = express.createServer();
var io    = require('socket.io').listen(app);

// Configuration

app.configure(function(){
  app.set('views', __dirname + '/views');
  app.set('view engine', 'jade');
  app.use(express.bodyParser());
  app.use(express.methodOverride());
  app.use(app.router);
  app.use(express.static(__dirname + '/public'));
});

app.configure('development', function(){
  app.use(express.errorHandler({ dumpExceptions: true, showStack: true })); 
});

app.configure('production', function(){
  app.use(express.errorHandler()); 
});

// Routes



app.get('/', routes.index);

app.listen(3000);

var level = 0;

serialPort.on("data", function (data) {
  level = parseInt(data);
});

io.sockets.on('connection', function (socket) {
  socket.on("get-level", function () {
    socket.emit("current-level", { level: level });
  });
});

console.log("Express server listening on port %d in %s mode", app.address().port, app.settings.env);
