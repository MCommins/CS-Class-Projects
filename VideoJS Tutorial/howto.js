
$('#mute').on('click', function(){
  console.log('hello');
  muteVideo();
});

$('#pause').on('click', function(){
  console.log('hello');
  pauseVideo();
});

$('#fullscreen').on('click', function(){
  console.log('hello');
  fullscreenVideo();
});

$(document).on('keydown', function() {
  if(event.which === 77) {
    console.log('hello');
    muteVideo();
  }
  else if (event.which === 80) {
    console.log('hello');
    pauseVideo();
  }
  else if (event.which === 70) {
    console.log('hello');
    fullscreenVideo();
  }
});

function muteVideo() {
  var myPlayer = videojs('#yellow-video');
  if(myPlayer.muted()) {
    myPlayer.muted(false);
    $('#output').text("Video Unmuted");
  }
  else if(!myPlayer.muted()) {
    myPlayer.muted(true);
    $('#output').text("Video Muted");
  }
}

function pauseVideo() {
  var myPlayer = videojs('#yellow-video');
  if(!myPlayer.paused()) {
    myPlayer.pause();
  }
  else if(myPlayer.paused()) {
    myPlayer.play();
  }
}

function fullscreenVideo() {
  var myPlayer = videojs('#yellow-video');
  myPlayer.requestFullscreen();
  $("#yellow-video > .vjs-big-play-button").hide();
}

$('#yellow-video').on("pause", function() {
  $('#output').text("Video Paused");
});

$('#yellow-video').on("play", function() {
  $('#output').text("Video is Now Playing");
});
