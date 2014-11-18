/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2013 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */

#include "CounterUIApplicationPCH.h"
#include <Vision/Runtime/Framework/VisionApp/VAppImpl.hpp>

#include <Vision/Runtime/Framework/VisionApp/Modules/VHelp.hpp>

#include <Vision/Runtime/EnginePlugins/ThirdParty/ScaleformEnginePlugin/VScaleformMovie.hpp>
#include <Vision/Runtime/EnginePlugins/ThirdParty/ScaleformEnginePlugin/VScaleformVariable.hpp>
#include <Vision/Runtime/EnginePlugins/ThirdParty/ScaleformEnginePlugin/VScaleformValue.hpp>
#include <Vision/Runtime/EnginePlugins/VisionEnginePlugin/Input/VFreeCamera.hpp>

//#include "GFx/GFx_Player.h"

// Use the following line to initialize a plugin that is statically linked.
// Note that only Windows platform links plugins dynamically (on Windows you can comment out this line).
VIMPORT IVisPlugin_cl* GetEnginePlugin_CounterUIPlugin();
VIMPORT IVisPlugin_cl* GetEnginePlugin_vScaleformPlugin();

#define AS_VERSION_2 2
#define AS_VERSION_3 3
#define CURRENT_AS_VERSION AS_VERSION_3

class CounterUIApplicationClass : public VAppImpl, public IVisCallbackHandler_cl
{
public:
  CounterUIApplicationClass() 
    : m_sMovieName("")
    , m_spMovie(NULL)
    , m_spMouse(NULL)
  {}

  virtual ~CounterUIApplicationClass() {}

  virtual void SetupAppConfig(VisAppConfig_cl& config) HKV_OVERRIDE;
  virtual void PreloadPlugins() HKV_OVERRIDE;

  virtual void Init() HKV_OVERRIDE;
  virtual void AfterSceneLoaded(bool bLoadingSuccessful) HKV_OVERRIDE;
  virtual bool Run() HKV_OVERRIDE;
  virtual void DeInit() HKV_OVERRIDE;

  void OnHandleCallback(IVisCallbackDataObject_cl *pData) HKV_OVERRIDE;

private:
  VString m_sMovieName;
  VScaleformMovieInstancePtr m_spMovie;
  VScaleformMovieInstancePtr m_spCounter;
  VisScreenMaskPtr m_spMouse;
};

VAPP_IMPLEMENT_SAMPLE(CounterUIApplicationClass);

void CounterUIApplicationClass::SetupAppConfig(VisAppConfig_cl& config)
{
  // Set custom file system root name ("havok_sdk" by default)
  config.m_sFileSystemRootName = "template_root";

  // Set the initial starting position of our game window and other properties
  // if not in fullscreen. This is only relevant on windows
  config.m_videoConfig.m_iXRes = 1136; // Set the Window size X if not in fullscreen.
  config.m_videoConfig.m_iYRes = 640;  // Set the Window size Y if not in fullscreen.
  config.m_videoConfig.m_iXPos = -1140;   // Set the Window position X if not in fullscreen.
  config.m_videoConfig.m_iYPos = -30;   // Set the Window position Y if not in fullscreen.

  // Name to be displayed in the windows title bar.
  config.m_videoConfig.m_szWindowTitle = "StandAlone Project Template";

  config.m_videoConfig.m_bWaitVRetrace = true;

  // Fullscreen mode with current desktop resolution
  
#if defined(WIN32)
  /*
  DEVMODEA deviceMode;
  deviceMode = Vision::Video.GetAdapterMode(config.m_videoConfig.m_iAdapter);
  config.m_videoConfig.m_iXRes = deviceMode.dmPelsWidth;
  config.m_videoConfig.m_iYRes = deviceMode.dmPelsHeight;
  config.m_videoConfig.m_bFullScreen = true;
  */
#endif
  
}

void CounterUIApplicationClass::PreloadPlugins()
{
  // Use the following line to load a plugin. Remember that, except on Windows platform, in addition
  // you still need to statically link your plugin library (e.g. on mobile platforms) through project
  // Properties, Linker, Additional Dependencies.
  VISION_PLUGIN_ENSURE_LOADED(CounterUIPlugin);
  VISION_PLUGIN_ENSURE_LOADED(vScaleformPlugin);
}

//---------------------------------------------------------------------------------------------------------
// Init function. Here we trigger loading our scene
//---------------------------------------------------------------------------------------------------------
void CounterUIApplicationClass::Init()
{
  // Set filename and paths to our stand alone version.
  // Note: "/Data/Vision/Base" is always added by the sample framework
  VisAppLoadSettings settings("Scenes/Default.vscene");
  settings.m_customSearchPaths.Append(":template_root/Assets");
  LoadScene(settings);

  VOnExternalInterfaceCall::OnExternalInterfaceCallback += this;
}

//---------------------------------------------------------------------------------------------------------
// Gets called after the scene has been loaded
//---------------------------------------------------------------------------------------------------------
void CounterUIApplicationClass::AfterSceneLoaded(bool bLoadingSuccessful)
{
  // Define some help text
  VArray<const char*> help;
  help.Append("How to use this demo...");
  help.Append("");
  RegisterAppModule(new VHelp(help));

  // Create a free camera
  VFreeCamera* pFreeCamera = vstatic_cast<VFreeCamera*>(Vision::Game.CreateEntity("VFreeCamera", hkvVec3::ZeroVector()));
  pFreeCamera->SetThinkFunctionStatus(false);
  
  // Create the mouse cursor
  m_spMouse = new VisScreenMask_cl("Textures\\UI\\mouseNorm.TGA");
  m_spMouse->SetTransparency(VIS_TRANSP_ALPHA);
  m_spMouse->SetVisible(true);
  VScaleformManager::GlobalManager().SetHandleCursorInput(true);

  VString strScoreName = "Flash\\scoreboard.swf";
  m_spCounter = VScaleformManager::GlobalManager().LoadMovie(strScoreName);
  if (m_spCounter==NULL)
  {
	  hkvLog::FatalError("Could not load movie: %s", strScoreName);
  }
  else
  {
	  VScaleformVariable myScore = m_spCounter->GetVariable("_root.myScore");
	  VScaleformValue value[1];
	  value[0] = 5000;
	  myScore.Invoke("add", value);
  }
}

//---------------------------------------------------------------------------------------------------------
// Main Loop of the application until we quit
//---------------------------------------------------------------------------------------------------------
bool CounterUIApplicationClass::Run()
{
  float x,y;
  VScaleformManager::GlobalManager().GetCursorPos(x,y);
  m_spMouse->SetPos(x,y);

  return true;
}

void CounterUIApplicationClass::DeInit()
{
  // De-Initialization
  // [...]
  VOnExternalInterfaceCall::OnExternalInterfaceCallback -= this;
}

//---------------------------------------------------------------------------------------------------------
// Receive command callbacks and external interface calls.
//---------------------------------------------------------------------------------------------------------
void CounterUIApplicationClass::OnHandleCallback(IVisCallbackDataObject_cl *pData)
{
  if(pData->m_pSender == &VOnExternalInterfaceCall::OnExternalInterfaceCallback)
  {  
    VOnExternalInterfaceCall *pExternalCall = (VOnExternalInterfaceCall *)pData;

    if(pExternalCall->m_sMethodName == "resetButton")
    {
      Vision::Message.Add(1, "Reset button pressed");

      #if CURRENT_AS_VERSION == AS_VERSION_2
        VScaleformVariable counterVar = m_spMovie->GetVariable("UI.count");
	  #else
	    VScaleformVariable counterVar = m_spMovie->GetVariable("_root.globalCount");
	  #endif

#if 1
		counterVar.SetNumber(0);
		VScaleformVariable labelVar =  m_spMovie->GetVariable("_root.countLabel.labelText.text");
		labelVar.SetString(":)");

#else
		VScaleformValue counter = m_spMovie->GetVariableValue("_root.globalCount");
		VScaleformValue label =  m_spMovie->GetVariableValue("_root.countLabel.labelText.text");
		counter.SetNumber(0);
		label.SetString("-");
#endif

      return;
    }
    if(pExternalCall->m_sMethodName == "addButton")
    {
      Vision::Message.Add(1, "Add 1 button pressed");

      #if CURRENT_AS_VERSION == AS_VERSION_2
        int countValue = static_cast<int>(m_spMovie->GetVariable("UI.count").GetNumber());
      #else           
        //VASSERT(m_spMovie->GetVariable("_root.globalCount")->IsNumeric()); // var globalCount:Number;
        int countValue = static_cast<int>(m_spMovie->GetVariable("_root.globalCount").GetNumber());
      #endif

      if (countValue == 1)
      {
        VScaleformVariable titleVar =  m_spMovie->GetVariable("_root.title.text");
        titleVar.SetString("Count to 10 to Exit!");
      }
      else if (countValue == 10)
      {
        VScaleformVariable labelVar =  m_spMovie->GetVariable("_root.countLabel.labelText.text");
          labelVar.SetString("Bye!");
        VAppBase::Get()->Quit();
      }

      return;
    }
  }
}


/*
 * Havok SDK - Base file, BUILD(#20131218)
 * 
 * Confidential Information of Havok.  (C) Copyright 1999-2013
 * Telekinesys Research Limited t/a Havok. All Rights Reserved. The Havok
 * Logo, and the Havok buzzsaw logo are trademarks of Havok.  Title, ownership
 * rights, and intellectual property rights in the Havok software remain in
 * Havok and/or its suppliers.
 * 
 * Use of this software for evaluation purposes is subject to and indicates
 * acceptance of the End User licence Agreement for this product. A copy of
 * the license is included with this software and is also available from salesteam@havok.com.
 * 
 */
