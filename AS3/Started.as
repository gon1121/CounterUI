package  {
	
	import flash.display.MovieClip;
	import flash.events.MouseEvent;
    import scaleform.clik.data.DataProvider;
	import flash.external.ExternalInterface;

	import scaleform.clik.controls.RadioButton;
    import scaleform.clik.controls.ButtonGroup;
    import scaleform.clik.events.ButtonEvent;
	
	public class Started extends MovieClip {
	
	public var optionButton:MovieClip;
	public var okButton:MovieClip;
	public var cancelButton:MovieClip;
	public var dificcultyStepper:MovieClip;
	public var labelMainMenu:MovieClip;
	public var labelOption:MovieClip;
	public var soundSlider:MovieClip;
	
	public var bloomButton:MovieClip;
	public var aaButton:MovieClip;
	public var edgeButton:MovieClip;
	public var hwButton:MovieClip;
	
	public var aaGroup:ButtonGroup;
	
		public function Started() 
		{
			initMainPage();
		}
		
		function initMainPage()
		{
			optionButton.addEventListener(MouseEvent.CLICK, onOptionClick);
		}
		
		function onOptionClick(event:MouseEvent):void 
		{
			ExternalInterface.call("optionButton");
			gotoAndStop(10);

			initOptionPage();
		}
		
		function initOptionPage()
		{
			okButton.addEventListener(MouseEvent.CLICK, onOkClick);
			cancelButton.addEventListener(MouseEvent.CLICK, onCancelClick);
			
			dificcultyStepper.dataProvider = new DataProvider([ "Easy", "Medium", "Hard", "Insane///"]);
			
			aaGroup = ButtonGroup.getGroup("aaGroup", this);
			//edgeButton.group = hwButton.group = aaGroup;
			aaGroup.addEventListener(Event.CHANGE, onChangeGroup, false, 0, true);

			aaButton.addEventListener(ButtonEvent.CLICK, enableAAGroup, false, 0, true);

			edgeButton.enabled = hwButton.enabled = aaButton.selected;
			aaGroup.setSelectedButtonByIndex(1, true);
		}

		function onChangeGroup(event:Event):void 
		{
			ExternalInterface.call("onChangeGroup");
		}
		
		function enableAAGroup(event:Event):void 
		{
			ExternalInterface.call("enableAAGroup");
			edgeButton.enabled = hwButton.enabled = aaButton.selected;
		}
		
		function onOkClick(event:MouseEvent):void 
		{
			ExternalInterface.call("okButton");
			gotoAndStop(1);

			initMainPage();
		}
		
		function onCancelClick(event:MouseEvent):void 
		{
			ExternalInterface.call("cancelButton");
			gotoAndStop(1);

			initMainPage();
		}
	}
}
