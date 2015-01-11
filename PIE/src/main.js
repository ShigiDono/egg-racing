require.config({
	shim: {
		'glUtils': {
			deps: ["sylvester"]
		},
		'glMatrix': {
			exports: ["mat4"]
		}
	}
});



require(["glMatrix"], function(gl_matrix) {
	function binaryFile(data) {
		this.data = new DataView(data);
	    this.byteArray = new Uint8Array(data);
		this.pos = 0;
		this.size = data.byteLength;
	}

	binaryFile.prototype = {
		read: function(count) {
			//console.log(this.pos, count);
			var result = this.byteArray.subarray(this.pos, this.pos + count);
			this.pos += count;
			return result;
		},
		readNullTerminatedString: function() {
			var oldPos = this.pos;
			while (this.pos < this.size && this.byteArray[this.pos]) this.pos++;
			return String.fromCharCode.apply(null, this.byteArray.subarray(oldPos, this.pos++));
		},
		readUint32: function() {
			var old_pos = this.pos;
			this.pos += 4;
			return this.data.getUint32(old_pos, true);
		},
		readFloat32: function() {
			var old_pos = this.pos;
			this.pos += 4;
			return this.data.getFloat32(old_pos, true);
		},
		readUint16: function(count) {
			var result = new Uint16Array(this.byteArray.buffer.slice(this.pos, this.pos + count*2));
			this.pos += count*2;
			return result;
		}
	};

	function Uint32ParserSpawner(_count) {
		return function(file, data) {
			var count;
			if (typeof _count == "function") {
				count = _count(data);
			} else {
				count = _count;
			}
			if (count == undefined || count == 1) {
				return file.readUint32();
			}
		}
	}
	function Float32ParserSpawner(_count) {
		return function(file, data) {
			var count;
			if (typeof _count == "function") {
				count = _count(data);
			} else {
				count = _count;
			}
			if (count == undefined || count == 1) {
				return file.readFloat32();
			}
		}
	}
	function Uint8ParserSpawner(_count) {
		return function(file, data) {
			var count;
			if (typeof _count == "function") {
				count = _count(data);
			} else {
				count = _count;
			}
			if (count == undefined || count == 1) {
				count = 1;
				return file.read(1)[0];
			}
			return file.read(count);
		}
	}
	function Uint16ParserSpawner(_count) {
		return function(file, data) {
			var count;
			if (typeof _count == "function") {
				count = _count(data);
			} else {
				count = _count;
			}
			if (count == undefined || count == 1) {
				count = 1;
				return file.readUint16(1)[0];
			}
			return file.readUint16(count);
		}
	}
	function texturesParserSpawner(_count) {
		return function(file, data) {
			var count;
			if (typeof _count == "function") {
				count = _count(data);
			} else {
				count = _count;
			}
			if (count == undefined) {
				count = 1;
			}
			var result = [];
			for (var i = 0; i < count; i++) {
				result.push(load(file, texturesDescription));
			}
			return result;
		}
	}
	function textureDataParserSpawner(_count) {
		return function(file, data) {
			var count;
			if (typeof _count == "function") {
				count = _count(data);
			} else {
				count = _count;
			}
			if (count == undefined) {
				count = 1;
				console.log("!!!");
			}
			if (count != 1) {
				console.log(count);
			}
			var result = [];
			for (var i = 0; i < count; i++) {
				result.push(load(file, textureDataDescription));
			}
			return result;
		}
	}
	function stringParserSpawner(count) {
		return function(file, data) {
			return file.readNullTerminatedString();
		}
	}
	Uint32Parser = Uint32ParserSpawner();
	Uint16Parser = Uint16ParserSpawner();
	Uint8Parser = Uint8ParserSpawner();
	Float32Parser = Float32ParserSpawner();
	stringParser = stringParserSpawner();
	var textureDataDescription = [
		['num', Uint16Parser],
		['coord', Uint16Parser]
	];
	var texturesDescription = [
		['n', Uint8Parser],
		['data', textureDataParserSpawner(function(data) {return data.n;})]
	];
	var pieMapDescription = [
		['header', "PMP"],
		['name', stringParser],
		['w', Uint32Parser],
		['h', Uint32Parser],
		['h_scale', Float32Parser],
		['v_scale', Float32Parser],
		['bg', Uint32Parser],
		['fnear', Float32Parser],
		['ffar', Float32Parser],
		['terrain', [
				['height_map', Uint8ParserSpawner(function(data) {return data.parent.w*data.parent.h;})],
				['temp_t', Uint16ParserSpawner(function(data) {return data.parent.w*data.parent.h;})],
				['ts', Uint32Parser],
				['t_width', Uint32Parser],
				['t_height', Uint32Parser],
				['t_count', Uint32Parser],
				['textures', texturesParserSpawner(function(data) {return data.t_count;})],
				['t_def', Uint32Parser],
				['t_def1', Uint32Parser],
			]
		],
	];

	function load(file, data, result) { // move parent here
		if (result == undefined) {
			result = {};
		}
		for (var i = 0; i < data.length; i++) {
			if (result.n > 1) {
				console.log(result.n);
			}
			if (typeof data[i][1] == "string") {
				if (String.fromCharCode.apply(null, file.read(data[i][1].length)) != data[i][1]) {
					console.error("Unknown format!");
				}
			} else if (typeof data[i][1] == "object") {
				result[data[i][0]] = load(file, data[i][1], {
					'parent': result
				});
			} else {
				result[data[i][0]] = data[i][1](file, result);
			}
		}
		return result;
	}

	function chunk(config, x, y, gl) {
		this.config = config;
		this.x = x;
		this.y = y;
		this.gl = gl;
		if (typeof chunk.index_buffer == "undefined") {
			this.initIndexBuffer(gl);
		}
		this.initVertexBuffer(gl);
	}
	chunk.size = 50;

	chunk.prototype = {
		initIndexBuffer: function(gl) {
			var indices = [];

			chunk.index_buffer = gl.createBuffer();
			gl.bindBuffer(gl.ELEMENT_ARRAY_BUFFER, chunk.index_buffer);

			for (var i = 0; i < chunk.size*chunk.size; i++) {
				indices.push(
					i*4 + 0, i*4 + 1, i*4 + 2,
					i*4 + 2, i*4 + 1, i*4 + 3
				);
			}
			m = 0;
			for (var i = 0; i < indices.length; i++) {
				m = Math.max(m, indices[i]);
			}
			//console.log(m, indices.length);
			gl.bufferData(gl.ELEMENT_ARRAY_BUFFER, new Uint16Array(indices), gl.STATIC_DRAW);
		},
		initVertexBuffer: function(gl) {
			var vertices = [];
			var color = [Math.random()/2 + 0.5, Math.random()/2 + 0.5, Math.random()/2 + 0.5];
			var max = this.config.w*this.config.h;
			this.vertex_count = 
				(Math.min(this.x + chunk.size, this.config.w) - this.x)*
				(Math.min(this.y + chunk.size, this.config.h) - this.y)*6;
			//check this on 

			// join to single buffer: done!
			for (var y = this.y; y < this.y + chunk.size; y++) {
				for (var x = this.x; x < this.x + chunk.size; x++) {
					if ((x + 1 > this.config.w) || (y + 1 > this.config.h)) {
						
					} else {
						vertices.push(
							x * this.config.h_scale, y * this.config.h_scale, this.get_height(x, y),
							color[0], color[1], color[2], 1,
							(x + 1) * this.config.h_scale, y * this.config.h_scale, this.get_height(x + 1, y),
							color[0], color[1], color[2], 1,
							x * this.config.h_scale, (y + 1) * this.config.h_scale, this.get_height(x, y + 1),
							color[0], color[1], color[2], 1,
							(x + 1) * this.config.h_scale, (y + 1) * this.config.h_scale, this.get_height(x + 1, y + 1),
							color[0], color[1], color[2], 1
						);
					}
				}
			}

			this.vertex_buffer = gl.createBuffer();
			gl.bindBuffer(gl.ARRAY_BUFFER, this.vertex_buffer);
			gl.bufferData(gl.ARRAY_BUFFER, new Float32Array(vertices), gl.STATIC_DRAW);
		},
		get_height: function(x, y) {
			var i = x + y*this.config.w;
			//if (i > ) {
			//	return 0;
			//}
			return this.config.terrain.height_map[i]*this.config.v_scale;
		},
		draw: function(current_shader) {
			if (!this.vertex_count) {
				return;
			}
			//translate to x*this.config.h_scale, 
			loadIdentity();
			//mvTranslate([this.x, this.y, 0]);

			gl.bindBuffer(gl.ARRAY_BUFFER, this.vertex_buffer);
			gl.vertexAttribPointer(current_shader.vertex, 3, gl.FLOAT, false, 28, 0);

			gl.bindBuffer(gl.ARRAY_BUFFER, this.vertex_buffer);
			gl.vertexAttribPointer(current_shader.color, 4, gl.FLOAT, false, 28, 12);//7*4, 3*4);
			setMatrixUniforms(current_shader);
			gl.drawElements(gl.TRIANGLES, this.vertex_count, gl.UNSIGNED_SHORT, 0);//gl.drawArrays(gl.TRIANGLES, 0, 9);//this.vertex_count);
		}
	}

	function terrain(config, gl) {
		this.config = config;
		this.gl = gl;
		this.chunks = [];
	}

	terrain.prototype = {
		init: function() {
			for (var y = 0; y < this.config.h/chunk.size; y++) {
				for (var x = 0; x < this.config.w/chunk.size; x++) {
					this.chunks.push(new chunk(this.config, x*chunk.size, y*chunk.size, gl));
				}
			}
		},
		draw: function() {
			for (var i = 0; i < this.chunks.length; i++) {
				this.chunks[i].draw(this.current_shader);
			}
		}
	}

	function loadMap(data) {
		var file = new binaryFile(data);

		var result = load(file, pieMapDescription);
		//console.log(String.fromCharCode.apply(null, file.read(3)));

		/*result.name = file.readNullTerminatedString();
		result.w = file.readUint();
		result.h = file.readUint();
		result.h_scale = file.readFloat();
		result.v_scale = file.readFloat();
		result.bg = file.readUint();

		result.fnear = file.readFloat();
		result.ffar = file.readFloat();*/
		console.log(result);
		return result;
	}

	function getShader(theSource, type) {
	  
	  var shader;
	  
	  if (type == "fragment") {
	    shader = gl.createShader(gl.FRAGMENT_SHADER);
	  } else if (type == "vertex") {
	    shader = gl.createShader(gl.VERTEX_SHADER);
	  } else {
	    return null;  // Unknown shader type
	  }
	  
	  // Send the source to the shader object
	  
	  gl.shaderSource(shader, theSource);
	  
	  // Compile the shader program
	  
	  gl.compileShader(shader);
	  
	  // See if it compiled successfully
	  
	  if (!gl.getShaderParameter(shader, gl.COMPILE_STATUS)) {
	    alert("An error occurred compiling the shaders: " + gl.getShaderInfoLog(shader));
	    return null;
	  }
	  
	  return shader;
	}


	function shader(vertex_shader, fragment_shader) {
		this.fragmentShader = getShader("\
	varying lowp vec4 vColor;\
	\
	void main(void) {\
	gl_FragColor = vColor;}", "fragment");
		this.vertexShader = getShader("\
	attribute vec3 aVertexPosition;\
	attribute vec4 aVertexColor;\
	\
	uniform mat4 uMVMatrix;\
	uniform mat4 uPMatrix;\
	\
		varying lowp vec4 vColor;\
	\
	void main(void) {\
	gl_Position = uPMatrix * uMVMatrix * vec4(aVertexPosition, 1.0);\
	vColor = aVertexColor*aVertexPosition.z/25.0;\
	      }", "vertex");

		// Create the shader program

		this.shaderProgram = gl.createProgram();
		gl.attachShader(this.shaderProgram, this.vertexShader);
		gl.attachShader(this.shaderProgram, this.fragmentShader);
		gl.linkProgram(this.shaderProgram);

		// If creating the shader program failed, alert

		if (!gl.getProgramParameter(this.shaderProgram, gl.LINK_STATUS)) {
			alert("Unable to initialize the shader program.");
		}

		gl.useProgram(this.shaderProgram);

		this.vertex = gl.getAttribLocation(this.shaderProgram, "aVertexPosition");
		gl.enableVertexAttribArray(this.vertex);

		this.color = gl.getAttribLocation(this.shaderProgram, "aVertexColor");
		gl.enableVertexAttribArray(this.color);
		this.pUniform = gl.getUniformLocation(this.shaderProgram, "uPMatrix");
		this.mvUniform = gl.getUniformLocation(this.shaderProgram, "uMVMatrix");


	}
	var mvMatrix = gl_matrix.mat4.create(), perspectiveMatrix = gl_matrix.mat4.create();
	var ti = 0;
	var c = [256, 256, 0], u = [0, 0, 1];
	function loadIdentity() {
	  gl_matrix.mat4.lookAt(mvMatrix, [256 + 256*Math.cos(ti), 256 + 256*Math.sin(ti), 256], c, u);//makeLookAt(256 + 256*Math.cos(ti), 256 + 256*Math.sin(ti), 256, 256, 256, 0, 0, 0, 1);//Matrix.I(4);
	}

	/*function multMatrix(m) {
	  mvMatrix = mvMatrix.x(m);
	}

	function mvTranslate(v) {
	  multMatrix(Matrix.Translation($V([v[0], v[1], v[2]])).ensure4x4());
	}*/

	function setMatrixUniforms(current_shader) {
		gl.uniformMatrix4fv(current_shader.pUniform, false, perspectiveMatrix);

		gl.uniformMatrix4fv(current_shader.mvUniform, false, mvMatrix);
	}

	function toggleFullScreen() {
	  if (!document.fullscreenElement &&    // alternative standard method
	      !document.mozFullScreenElement && !document.webkitFullscreenElement && !document.msFullscreenElement ) {  // current working methods
	    if (document.documentElement.requestFullscreen) {
	      document.documentElement.requestFullscreen();
	    } else if (document.documentElement.msRequestFullscreen) {
	      document.documentElement.msRequestFullscreen();
	    } else if (document.documentElement.mozRequestFullScreen) {
	      document.documentElement.mozRequestFullScreen();
	    } else if (document.documentElement.webkitRequestFullscreen) {
	      document.documentElement.webkitRequestFullscreen(Element.ALLOW_KEYBOARD_INPUT);
	    }
	  } else {
	    if (document.exitFullscreen) {
	      document.exitFullscreen();
	    } else if (document.msExitFullscreen) {
	      document.msExitFullscreen();
	    } else if (document.mozCancelFullScreen) {
	      document.mozCancelFullScreen();
	    } else if (document.webkitExitFullscreen) {
	      document.webkitExitFullscreen();
	    }
	  }
	}
	var last = 0;
	function initGL(canvas) {
		gl = null;
		try {
			gl = canvas.getContext("webgl") || canvas.getContext("experimental-webgl");
		} catch (e) {

		}
		if (!gl) {
			alert("Fail");
			gl = null;
		} else {
			gl.clearColor(0, 0, 0, 1);
			gl.enable(gl.DEPTH_TEST);
			gl.depthFunc(gl.LEQUAL);
			gl.clear(gl.COLOR_BUFFER_BIT | gl.DEPTH_BUFFER_BIT);
			gl.viewport(0, 0, canvas.width, canvas.height);
		}
		var elem = canvas;
		canvas.addEventListener("mousedown", function(e) {
	    	toggleFullScreen();
		}, false);
		canvas.addEventListener("touchstart", function(e) {
			if (Date.now() - last < 3000) {
				return;
			}
			last = Date.now();
	    	//toggleFullScreen();
		}, false);

		return gl;
	}
	document.addEventListener("keydown", function(e) {
	  if (e.keyCode == 13) {
	    toggleFullScreen();
	  }
	}, false);


	perspectiveMatrix = gl_matrix.mat4.perspective(perspectiveMatrix, 1.4, 640.0/640.0, 0.1, 1000.0);
	
	loadIdentity();
	var oReq = new XMLHttpRequest();
	oReq.open("GET", "bin/Data/Maps/GreenForest.pm", true);
	oReq.responseType = "arraybuffer";

	var gl = initGL(document.getElementById("glcanvas"));
	current_shader = new shader();
	gl.useProgram(current_shader.shaderProgram);

	var t;

	oReq.onload = function (oEvent) {
	  var arrayBuffer = oReq.response; // Note: not oReq.responseText
	  if (arrayBuffer) {
	    t = new terrain(loadMap(arrayBuffer), gl);
	    t.current_shader = current_shader;
	    t.init();
	  }
	};

	oReq.send(null);
	var requestAnimationFrame = window.requestAnimationFrame || window.mozRequestAnimationFrame ||
                              window.webkitRequestAnimationFrame || window.msRequestAnimationFrame;
  	window.requestAnimationFrame = requestAnimationFrame;

	function draw(time) {
		gl.clear(gl.COLOR_BUFFER_BIT|gl.DEPTH_BUFFER_BIT);
		ti = Date.now()/1000.0;

		if (typeof t != "undefined") {
			t.draw();
		}
		requestAnimationFrame(draw);
	}
	requestAnimationFrame(draw);



});