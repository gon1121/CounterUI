package  {
	
	import flash.display.MovieClip;
	import flash.events.Event;
	import flash.text.TextField;
	
	public class DamageFont extends MovieClip {
		
		private var SPEED:int = 5; // how fast to count
		private const MAX_FRAME:int = 25;
		private var _damage:int = 1234567890;
		private var _frame:int = 0;

		public var damageText:TextField;
		
		public function DamageFont() {
		}
		
		public function set(val:int): void
		{
			_damage = val;
			damageText.text = val.toString();
			addEventListener(Event.ENTER_FRAME, updateScoreDisplay);
		}

		public function updateScoreDisplay(e:Event):void {
			this.y -= SPEED;
			this.alpha -= (1.0 / 25);
			_frame += 1;
			
			if (_frame >= MAX_FRAME)
				removeEventListener(Event.ENTER_FRAME, updateScoreDisplay);
		}
	}
}
