module Html = Dom_html
				
let canvas = Html.getElementById "can" in
	Graphics.open_canvas canvas;
