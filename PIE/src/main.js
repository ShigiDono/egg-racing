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
	var vec3 = gl_matrix.vec3;
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
			}
			var result = [];
			for (var i = 0; i < count; i++) {
				result.push(load(file, textureDataDescription));
			}
			return result;
		}
	}
	function stringParserSpawner(_count) {
		return function(file, data) {
			var count;
			if (typeof _count == "function") {
				count = _count(data);
			} else {
				count = _count;
			}
			if (count == undefined || count == 1) {
				return file.readNullTerminatedString();
			}
			var result = [];
			while (count) {
				result.push(file.readNullTerminatedString());
				count--;
			}
			return result;
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
				['t_coord', Uint16ParserSpawner(function(data) {return data.parent.w*data.parent.h;})],
				['ts', Uint32Parser],
				['t_width', Uint32Parser],
				['t_height', Uint32Parser],
				['t_count', Uint32Parser],
				['textures_data', texturesParserSpawner(function(data) {return data.t_count;})],
				['t_def', Uint32Parser],
				['t_def1', Uint32Parser],
				['textures_count', Uint32Parser],
				['textures', stringParserSpawner(function(data) {return data.textures_count})],
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
			var t, s;
			for (var y = this.y; y < this.y + chunk.size; y++) {
				for (var x = this.x; x < this.x + chunk.size; x++) {
					if ((x + 1 > this.config.w) || (y + 1 > this.config.h)) {
						
					} else {
						//t = (this.config.terrain.t_coord[x + y*this.config.w] % this.config.terrain.t_width) / this.config.terrain.t_width;
						//uv[1] = Math.floor(this.config.terrain.t_coord[x + y*this.config.w] / this.config.terrain.t_width) / this.config.terrain.t_height;
						this.generate_color(x, y);
						this.generate_color(x + 1, y);
						this.generate_color(x, y + 1);
						this.generate_color(x + 1, y + 1);
						vertices.push(
							x * this.config.h_scale, y * this.config.h_scale, this.get_height(x, y),
							this.config.terrain.colors[x + y*this.config.w][0], this.config.terrain.colors[x + y*this.config.w][1], this.config.terrain.colors[x + y*this.config.w][2], 1,
							//color[0], color[1], color[2], 1,
								(this.config.terrain.t_coord[x + y*this.config.w] % this.config.terrain.t_width) / this.config.terrain.t_width,
								Math.floor(this.config.terrain.t_coord[x + y*this.config.w] / this.config.terrain.t_width) / this.config.terrain.t_height,
							(x + 1) * this.config.h_scale, y * this.config.h_scale, this.get_height(x + 1, y),
							this.config.terrain.colors[x + 1 + y*this.config.w][0], this.config.terrain.colors[x + 1 + y*this.config.w][1], this.config.terrain.colors[x + 1 + y*this.config.w][2], 1,
							//color[0], color[1], color[2], 1,
								(this.config.terrain.t_coord[x + y*this.config.w] % this.config.terrain.t_width) / this.config.terrain.t_width,
								Math.floor(this.config.terrain.t_coord[x + y*this.config.w] / this.config.terrain.t_width + 1) / this.config.terrain.t_height,
							x * this.config.h_scale, (y + 1) * this.config.h_scale, this.get_height(x, y + 1),
							this.config.terrain.colors[x + (y + 1)*this.config.w][0], this.config.terrain.colors[x + (y + 1)*this.config.w][1], this.config.terrain.colors[x + (y + 1)*this.config.w][2], 1,
							//color[0], color[1], color[2], 1,
								(this.config.terrain.t_coord[x + y*this.config.w] % this.config.terrain.t_width + 1) / this.config.terrain.t_width,
								Math.floor(this.config.terrain.t_coord[x + y*this.config.w] / this.config.terrain.t_width) / this.config.terrain.t_height,
							(x + 1) * this.config.h_scale, (y + 1) * this.config.h_scale, this.get_height(x + 1, y + 1),
							this.config.terrain.colors[x + 1 + (y + 1)*this.config.w][0], this.config.terrain.colors[x + 1 + (y + 1)*this.config.w][1], this.config.terrain.colors[x + 1 + (y + 1)*this.config.w][2], 1,
							//color[0], color[1], color[2], 1,
								(this.config.terrain.t_coord[x + y*this.config.w] % this.config.terrain.t_width + 1) / this.config.terrain.t_width,
								Math.floor(this.config.terrain.t_coord[x + y*this.config.w] / this.config.terrain.t_width + 1) / this.config.terrain.t_height
						);
					}
				}
			}

			this.vertex_buffer = gl.createBuffer();
			gl.bindBuffer(gl.ARRAY_BUFFER, this.vertex_buffer);
			gl.bufferData(gl.ARRAY_BUFFER, new Float32Array(vertices), gl.STATIC_DRAW);
		},
		generate_color: function(x, y) {
			if (typeof this.config.terrain.colors == "undefined") {
				this.config.terrain.colors = [];
				this.config.terrain.normal = [];
			}
			if (this.config.terrain.colors[x + y*this.config.w]) {
				return;// this.config.terrain.colors[x + y*this.config.w];
			}
			var x_d = [0, 1, 1, 0, -1, -1];
			var y_d = [-1, -1, 0, 1, 1, 0];
			var p, f;
			var accum = vec3.create();
			var cross = vec3.create();
			var cnt = 0;
			for (var i = 0; i < 6; i++) {
				if (x + x_d[i] >= 0 && x + x_d[i] < this.config.w && y + y_d[i] >= 0 && y + y_d[i] < this.config.h) {
					var c = vec3.fromValues(-x_d[i]*this.config.h_scale, -y_d[i]*this.config.h_scale, this.get_height(x, y) - this.get_height(x + x_d[i], y + y_d[i]));
					if (!p) {
						p = c;
						f = p;
					} else {
						vec3.cross(cross, p, c);
						vec3.add(accum, accum, cross);
						p = c;
						cnt++;
					}
				} else {
					p = null;
					f = null;
				}
			}
			if (f) {
				vec3.cross(cross, c, f);
				vec3.add(accum, accum, cross);
			}
			vec3.normalize(accum, accum);
			var d = vec3.dot(accum, vec3.fromValues(0.9, 0.9, 0.9)) + 0.1;
			this.config.terrain.normal[x + y*this.config.w] = accum;
			this.config.terrain.colors[x + y*this.config.w] = [d, d, d];
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
			gl.vertexAttribPointer(current_shader.vertex, 3, gl.FLOAT, false, 36, 0);

			gl.bindBuffer(gl.ARRAY_BUFFER, this.vertex_buffer);
			gl.vertexAttribPointer(current_shader.color, 4, gl.FLOAT, false, 36, 12);//7*4, 3*4);

			gl.bindBuffer(gl.ARRAY_BUFFER, this.vertex_buffer);
			gl.vertexAttribPointer(current_shader.texture, 2, gl.FLOAT, false, 36, 28);//7*4, 3*4);

			setMatrixUniforms(current_shader);
			gl.drawElements(gl.TRIANGLES, this.vertex_count, gl.UNSIGNED_SHORT, 0);//gl.drawArrays(gl.TRIANGLES, 0, 9);//this.vertex_count);
		}
	}

	var getJSON = function(url, successHandler, errorHandler) {
		var xhr = typeof XMLHttpRequest != 'undefined'
		? new XMLHttpRequest()
		: new ActiveXObject('Microsoft.XMLHTTP');
		xhr.open('get', url, true);
		xhr.responseType = 'json';
		xhr.onreadystatechange = function() {
			var status;
			var data;
			// http://xhr.spec.whatwg.org/#dom-xmlhttprequest-readystate
			if (xhr.readyState == 4) { // `DONE`
				status = xhr.status;
				if (status == 200) {
					successHandler && successHandler(xhr.response);
				} else {
					errorHandler && errorHandler(status);
				}
			}
		};
		xhr.send();
	};

	function texture(file) {
		this.file = file;
	}

	texture.prototype = {
		load: function(callback) {
			var self = this;
			getJSON("bin/" + this.file + ".json", function(response) {
				self.data = response;
				self.img = new Image();
        		self.img.onload = function() {
	        		callback();
        		};
        		self.img.src = "bin/" + self.data.file;
			}, function (status) {
				callback(status);
			});
		},
		drawTile: function(context, tile, x, y, size) {
			var sx = 0, sy = 0, sw = this.img.width, sh = this.img.height;
			if (this.data.tiling.enabled) {
				sx = (tile * this.data.tiling.x) % this.img.width;
				sy = Math.floor(tile * this.data.tiling.x / this.img.width) * this.data.tiling.y;
				sw = this.data.tiling.x;
				sh = this.data.tiling.y;
			}
			context.drawImage(this.img, sx, sy, sw, sh, x, y, size, size);
		}
	};

	function terrain(config, gl) {
		this.config = config;
		this.gl = gl;
		this.chunks = [];
	}

	terrain.prototype = {
		init: function() {
			var images_loaded = 0;
			for (var i = 0; i < this.config.terrain.textures.length; i++) {
				this.config.terrain.textures[i] = new texture(this.config.terrain.textures[i]);
				var self = this;
				this.config.terrain.textures[i].load(function(err) {
					if (err) {
						console.log(err);
					} else {
						images_loaded++;
						if (images_loaded == self.config.terrain.textures.length) {
							self.generate_texture();
						}
					}
				});
			}
			for (var y = 0; y < this.config.h / chunk.size; y++) {
				for (var x = 0; x < this.config.w / chunk.size; x++) {
					this.chunks.push(new chunk(this.config, x * chunk.size, y * chunk.size, gl));
				}
			}
		},
		draw: function() {
			if (this.texture) {
				gl.activeTexture(gl.TEXTURE0);
    			gl.bindTexture(gl.TEXTURE_2D, this.texture);
	    		gl.uniform1i(current_shader.samplerUniform, 0);
    		}
			for (var i = 0; i < this.chunks.length; i++) {
				this.chunks[i].draw(this.current_shader);
			}
		},
		generate_texture: function() {
			var canvas = document.createElement('canvas');
			canvas.width = this.config.terrain.t_width*this.config.terrain.ts;
			canvas.height = this.config.terrain.t_height*this.config.terrain.ts;
			var ctx = canvas.getContext('2d');
			for (var i = 0; i < this.config.terrain.t_width*this.config.terrain.t_height; i++) {
				if (i < this.config.terrain.t_count) {
					for (var j = 0; j < this.config.terrain.textures_data[i].data.length; j++) {
						this.config.terrain.textures[this.config.terrain.textures_data[i].data[j].num].drawTile(
							ctx,
							this.config.terrain.textures_data[i].data[j].coord,
							(i % this.config.terrain.t_width) * this.config.terrain.ts,
							Math.floor(i / this.config.terrain.t_width) * this.config.terrain.ts,
							this.config.terrain.ts);
					}
				} else {
					this.config.terrain.textures[this.config.terrain.textures_data[0].data[0].num/*this.config.terrain.textures_data[this.config.terrain.t_def].data[j].num*/].drawTile(
						ctx,
						this.config.terrain.textures_data[0].data[0].coord,
						(i % this.config.terrain.t_width) * this.config.terrain.ts,
						Math.floor(i / this.config.terrain.t_width) * this.config.terrain.ts,
						this.config.terrain.ts);

				}
			}
			this.texture = gl.createTexture();
			gl.pixelStorei(gl.UNPACK_FLIP_Y_WEBGL, true);

			gl.bindTexture(gl.TEXTURE_2D, this.texture);
			gl.texImage2D(gl.TEXTURE_2D, 0, gl.RGBA, gl.RGBA, gl.UNSIGNED_BYTE, canvas); // This is the important line!
			gl.texParameteri(gl.TEXTURE_2D, gl.TEXTURE_MAG_FILTER, gl.LINEAR);
			gl.texParameteri(gl.TEXTURE_2D, gl.TEXTURE_MIN_FILTER, gl.LINEAR_MIPMAP_NEAREST);
			gl.generateMipmap(gl.TEXTURE_2D);

			gl.bindTexture(gl.TEXTURE_2D, null);

			//document.body.appendChild(canvas);
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
	varying highp vec2 vTextureCoord;\
\
  	uniform sampler2D uSampler;	\
	void main(void) {\
	gl_FragColor = vColor*texture2D(uSampler, vec2(vTextureCoord.s, 1.0 - vTextureCoord.t));\
	}", "fragment");
		this.vertexShader = getShader("\
	attribute vec3 aVertexPosition;\
	attribute vec4 aVertexColor;\
	attribute vec2 aTexture;\
	\
	uniform mat4 uMVMatrix;\
	uniform mat4 uPMatrix;\
	\
	varying lowp vec4 vColor;\
	varying vec2 vTextureCoord;\
	\
	void main(void) {\
	gl_Position = uPMatrix * uMVMatrix * vec4(aVertexPosition, 1.0);\
	vColor = aVertexColor/*aVertexPosition.z/25.0*/;\
	vTextureCoord = aTexture;\
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
		this.texture = gl.getAttribLocation(this.shaderProgram, "aTexture");
		gl.enableVertexAttribArray(this.texture);

		this.color = gl.getAttribLocation(this.shaderProgram, "aVertexColor");
		gl.enableVertexAttribArray(this.color);
		this.pUniform = gl.getUniformLocation(this.shaderProgram, "uPMatrix");
		this.mvUniform = gl.getUniformLocation(this.shaderProgram, "uMVMatrix");
		this.samplerUniform = gl.getUniformLocation(this.shaderProgram, "uSampler");


	}
	var mvMatrix = gl_matrix.mat4.create(), perspectiveMatrix = gl_matrix.mat4.create();
	var ti = 0;
	var c = [256, 256, 0], u = [0, 0, 1];
	function loadIdentity() {
	  gl_matrix.mat4.lookAt(mvMatrix, [256 + 256*Math.cos(ti), 256 + 256*Math.sin(ti), 256], c, u);//makeLookAt(256 + 256*Math.cos(ti), 256 + 256*Math.sin(ti), 256, 256, 256, 0, 0, 0, 1);//Matrix.I(4);
//	  gl_matrix.mat4.lookAt(mvMatrix, [70, 5, 32], [0,0,10], u);//makeLookAt(256 + 256*Math.cos(ti), 256 + 256*Math.sin(ti), 256, 256, 256, 0, 0, 0, 1);//Matrix.I(4);
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