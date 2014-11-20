/**************************************************************************

Filename    :   Icon.as
Content    :   
                


Copyright   :   Copyright 2011 Autodesk, Inc. All Rights reserved.

Use of this software is subject to the terms of the Autodesk license
agreement provided at the time of installation or download, or which
otherwise accompanies this software in either electronic or hard copy form.

**************************************************************************/
package  {
	
	import flash.display.Bitmap;
	import flash.display.MovieClip;
	import flash.display.Loader;
	import flash.system.LoaderContext;
	import flash.events.Event;
	import flash.net.URLRequest;
	import flash.text.TextField;
	
	public class Icon extends MovieClip {
		
	public var canvas:IconCanvas;
	public var tf_Bind:TextField;
	public var tf_Count:TextField;
	// Constants:
	
	// Public Properties:
		
	// Protected Properties:
		protected var _imageLoader:Loader;
		
	// UI Elements:
		
	// Initialization:
		public function Icon() {
			super();
			_imageLoader = new Loader();
			addChild(_imageLoader);
		}
		
	// Public Getter / Setters:
		
	// Public Methods:
		public function loadImage( imagePath:String ):void {
			removeChild( _imageLoader );
			if (_imageLoader.numChildren > 0) {
				_imageLoader.unload();
			}
			
			if (!imagePath || imagePath == "") { return; }
			//var url:URLRequest = new URLRequest( "img://icon:" + imagePath ); 
			var url:URLRequest = new URLRequest( imagePath ); 
			var context:LoaderContext = new LoaderContext(false, null);
			_imageLoader.contentLoaderInfo.addEventListener(Event.COMPLETE, handleImageLoadComplete, false, 0, true);
			_imageLoader.load(url, context);
		}
		
		protected function handleImageLoadComplete(e:Event):void {
			var bm:Bitmap = Bitmap(_imageLoader.content);
			bm.smoothing = true;
			addChild(_imageLoader);
		}
	
	// Protected Methods:
		override public function toString():String { 
			return "[MMOKit Icon " + name + "]";
		}
	}
}