package  {
	
	import flash.display.MovieClip;
    import flash.text.TextField;
    import flashx.textLayout.formats.Float;

	import scaleform.clik.data.DataBinding;
	
	public class UnitFrame extends MovieClip {
		
        public var tf_Name:TextField;
        public var tf_Level:TextField;
        public var unitType:MovieClip;
        public var unitHealthBar:MovieClip;
        public var unitManaBar:MovieClip;
		
		public function UnitFrame() {
            super();
            configUI();
        }
        
        protected function configUI():void {           
            DataBinding.createBinding("player.name", setName, this);
            DataBinding.createBinding("player.level", setLevel, this);
        }
        
        protected function setName(value:String):void {
            tf_Name.text = value;
        }
        protected function setLevel(value:String):void {
            tf_Level.text = value;
        }
		
        public function setHp(val:int):void {
            unitHealthBar.scaleX = val / 100;
        }
	}
	
}
