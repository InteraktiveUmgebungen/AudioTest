using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Speech.Recognition;
//using Microsoft.Speech.Recognition;


namespace AudioInput
{
    class Program
    {
        static void Main(string[] args)
        {
            init();
            run();
        }

        static void init()
        {
            // Show all installed recognizers
            Console.WriteLine("Installed Recognizers:");
            RecognizerInfo info = null;
            foreach (RecognizerInfo ri in SpeechRecognitionEngine.InstalledRecognizers())
            {
                Console.WriteLine(ri.Description);
                if (ri.Culture.TwoLetterISOLanguageName.Equals("de"))
                {
                    info = ri;
                    break;
                }
            }
            Console.WriteLine("--------");

            if (info != null)
            {
                Console.WriteLine("Loading Speech Recognition " + info.Description);
                // Create a new SpeechRecognitionEngine instance.
                SpeechRecognitionEngine sre = new SpeechRecognitionEngine(info);

                // Configure the input to the recognizer.
                sre.SetInputToDefaultAudioDevice();

                // Load a new Dictation Grammar
                sre.LoadGrammar(new DictationGrammar());

                // Register a handler for the SpeechRecognized event.
                sre.SpeechRecognized +=
                  new EventHandler<SpeechRecognizedEventArgs>(sre_SpeechRecognized);

                sre.SpeechHypothesized += new EventHandler<SpeechHypothesizedEventArgs>(sre_SpeechHypothesized);

                // Start recognition.
                sre.RecognizeAsync(RecognizeMode.Multiple);
            }
            else
            {
                throw new Exception("No Speech Recognition Installed!");
            }
        }

        static void sre_SpeechHypothesized(object sender, SpeechHypothesizedEventArgs e)
        {
            Console.WriteLine("I guess I heard:     " + e.Result.Text);
        }

        // Create a simple handler for the SpeechRecognized event.
        static void sre_SpeechRecognized(object sender, SpeechRecognizedEventArgs e)
        {
            Console.WriteLine("I'm sure that you said:     " + e.Result.Text);
            Console.WriteLine("_______________________________________");
        }

        static void run()
        {
            while (true)
            {
                Console.ReadLine();
            }
        }
    }
}