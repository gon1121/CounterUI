package  {
	
	import flash.display.MovieClip;
	import flash.events.Event;
	
	public class Score extends MovieClip {

		private var SPEED:int = 1; // how fast to count
		private const NUM_DIGITS:int = 7; // how many digits there are in the score

		private var _totalScore:int = 0;
		private var _displayScore:int= 0;
	
		public var digit1:MovieClip;
		public var digit2:MovieClip;
		public var digit3:MovieClip;
		public var digit4:MovieClip;
		public var digit5:MovieClip;
		public var digit6:MovieClip;
		public var digit7:MovieClip;
		public var digit8:MovieClip;
		
		public function Score() {
			// constructor code
		}

		// public accessor for totalScore
		public function get totalScore():int {
			return _totalScore;
		}
	
		// add an amount to the score
		public function add(amount:int):void {
			if (amount > 900)
				SPEED = 9;
			else if (amount > 100)
			 	SPEED = 3;
			else
				SPEED = 1;
				
			_totalScore += amount;
			addEventListener(Event.ENTER_FRAME, updateScoreDisplay);
			
		}
		
		public function set(amount:int):void {
			add(amount-_totalScore);
		}

		public function updateScoreDisplay(e:Event):void {
			_displayScore += SPEED; 
			
			// make sure the display score is not higher than the actual score
			if(_displayScore > _totalScore){
				_displayScore = _totalScore;
			}
			
			var scoreStr:String = String(_displayScore); // cast displayScore as a String
	 
			// add leading zeros
			while(scoreStr.length <= NUM_DIGITS){
				scoreStr = "0" + scoreStr;
			}
			
			// loop through and update each digit
			for (var i:int = 0; i <= NUM_DIGITS; i++) {
				var num = int(scoreStr.charAt(i));
				this["digit"+(i+1)].gotoAndStop(num+1);
				// set the digit mc to the right frame
			}
			
			// if the display score is equal to the total score remove the enterframe event
			if(_totalScore == _displayScore){
				removeEventListener(Event.ENTER_FRAME, updateScoreDisplay);
			}
		}
	}
}
