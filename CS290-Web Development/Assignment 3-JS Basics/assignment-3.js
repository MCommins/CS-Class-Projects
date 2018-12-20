window.onload = function () {

	clearTiles = function() {
		for(var i = 0; i < 12; i++) {
			if(document.getElementById('tile'+i) != null) {
				toggleDiv('tile'+i);
			}
		}
	}


	populateTiles = function() {
		for(var i = 0; i < 12; i++) {
			var titleNum = i+1;
			document.getElementById('tileDiv').insertAdjacentHTML('beforeend', '<div class="tile" id="tile' + i + '" >'
				+ '<p class="tileP" onClick=' + "'" + 'toggleDiv("tile' + i + '")' + "'" + ' > x </p>'
				+ '<img id="titleimage' + i + '" class="tileI"'
				+ ' src="https://encrypted-tbn0.gstatic.com/images?q=tbn:ANd9GcTgyqgkdxbpy8gUbGAl1hH-oLvQtEpWsm7X4KbC00KzUfsRXJQ7"/>'
				+ '<p>' + 'Tile' + titleNum + '</p>'
				+ '</div>')
		}
	}

	toggleDiv = function (identifier) {
		document.getElementById(identifier).parentNode.removeChild(document.getElementById(identifier));
	}

	resetTiles = function () {
		clearTiles();
		populateTiles();
	}

	populateTiles();

	roundImageSources = ['mt1.jpg','http://www.ancient-origins.net/sites/default/files/styles/large/public/Mount-Shasta.jpg?itok=_g7e-Al5','https://static.pexels.com/photos/67517/pexels-photo-67517.jpeg' ];

	imageCount = 0;

	switchImage = function () {
		if (imageCount >= roundImageSources.length) {
			imageCount = 0;
		}

		document.getElementById('roundImage').src = roundImageSources[imageCount];
		imageCount += 1;
	}

	changeText = function (target) {
		remakeText = function () {
			var paragraph = document.createElement('p');
			paragraph.innerHTML = textBox.value;
			paragraph.id = 'editable';
			paragraph.setAttribute('ondblclick', 'changeText(this)');
			newForm.replaceWith(paragraph);
		}
		var text = target.innerHTML;
		var newForm = document.createElement('form');
		newForm.setAttribute('method', 'POST');
		newForm.setAttribute('onsubmit', 'return remakeText()');

		var textBox = document.createElement('textarea');
		textBox.innerHTML = text;
		textBox.id = "textEditForm";

		var submit = document.createElement('input');
		submit.setAttribute('type','submit');
		submit.setAttribute('value','Submit');

		newForm.appendChild(textBox);
		newForm.appendChild(submit);
		target.replaceWith(newForm);
	}
}
