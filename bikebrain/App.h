#ifndef BIKEBRAIN_APP_H
#define BIKEBRAIN_APP_H

#include <bikebrain/IButton.h>
#include <bikebrain/ICadenceReporter.h>
#include <bikebrain/IDisplay.h>
#include <bikebrain/IDistanceSensor.h>
#include <bikebrain/IFont.h>
#include <bikebrain/IGpsModule.h>
#include <bikebrain/ILedMatrix.h>
#include <bikebrain/IStatsEngine.h>
#include <bikebrain/ITextDisplay.h>

#include <stingraykit/ObservableValue.h>
#include <stingraykit/log/Logger.h>
#include <stingraykit/timer/Timer.h>
#include <stingraykit/toolkit.h>

namespace bikebrain
{

	class App
	{
		struct TurnIndicatorState
		{
			STINGRAYKIT_ENUM_VALUES(None, Left, Right);
			STINGRAYKIT_DECLARE_ENUM_CLASS(TurnIndicatorState);
		};

	private:
		static stingray::NamedLogger					s_logger;

		stingray::ElapsedTime							_elapsedTime;

		stingray::ObservableValue<TurnIndicatorState>	_turnIndicatorState;
		stingray::ObservableValue<bool>					_activeTripState;

		IGpsModulePtr									_gpsModule;
		IButtonPtr										_leftButton;
		IButtonPtr										_rightButton;
		IButtonPtr										_controlButton;
		ILedMatrixPtr									_ledMatrix;
		ICadenceReporterPtr								_cadenceReporter;
		IDistanceSensorPtr								_distanceSensor;
		ITextDisplayPtr									_textDisplay;
		IFontPtr										_font;
		IStatsEnginePtr									_statsEngine;
		ITripPtr										_trip;

		stingray::ITaskExecutorPtr						_dataReportWorker;
		stingray::TimerPtr								_timer;

		stingray::TokenPool								_tokens;

	public:
		App();
		~App();

		void Run();

	private:
		void ButtonPressedHandler(const std::string& button, stingray::u32 ms);
		void TurnIndicatorStateChangedHandler(TurnIndicatorState state);
		void ActiveTripStateChangedHandler(bool state);

		void UpdateTurnIndicator();

		void PollDataFunc();

		void DoStartTrip();
		void DoStopTrip();
		void DoReportData(const DataEntry& dataEntry);
	};

}

#endif
