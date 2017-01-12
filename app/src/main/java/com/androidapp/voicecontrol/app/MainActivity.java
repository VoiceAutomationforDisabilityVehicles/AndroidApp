package com.androidapp.voicecontrol.app;
import java.util.ArrayList;

import android.graphics.Color;
import android.os.Bundle;
import android.app.Activity;
import android.content.Intent;
import android.view.View;
import android.view.View.OnClickListener;
import android.widget.Button;
import android.widget.ListView;
import android.speech.RecognizerIntent;
import android.widget.TextView;

public class MainActivity extends Activity implements OnClickListener {

    String[] retractKeys = {"close", "fold", "retract"};
    String[] openKeys = {"open", "out",};

    public ListView mList;
    public Button speakButton, status;
    private TextView txtSpeechInput;

    public static final int VOICE_RECOGNITION_REQUEST_CODE = 1234;

    @Override
    public void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        txtSpeechInput = (TextView) findViewById(R.id.txtSpeechInput);

        status = (Button) findViewById(R.id.status);

        speakButton = (Button) findViewById(R.id.btnSpeak);
        speakButton.setOnClickListener(this);

        voiceinputbuttons();
    }

    public void informationMenu() {
        startActivity(new Intent("android.intent.action.INFOSCREEN"));
    }

    public void voiceinputbuttons() {
        speakButton = (Button) findViewById(R.id.btnSpeak);
        //mList = (ListView) findViewById(R.id.list);
    }

    public void startVoiceRecognitionActivity() {
        Intent intent = new Intent(RecognizerIntent.ACTION_RECOGNIZE_SPEECH);
        intent.putExtra(RecognizerIntent.EXTRA_LANGUAGE_MODEL,
                RecognizerIntent.LANGUAGE_MODEL_FREE_FORM);
        intent.putExtra(RecognizerIntent.EXTRA_PROMPT,
                "Speech recognition demo");
        startActivityForResult(intent, VOICE_RECOGNITION_REQUEST_CODE);
    }

    public void onClick(View v) {
        // TODO Auto-generated method stub
        startVoiceRecognitionActivity();
    }

    @Override
    public void onActivityResult(int requestCode, int resultCode, Intent data) {
        super.onActivityResult(requestCode, resultCode, data);



        if (requestCode == VOICE_RECOGNITION_REQUEST_CODE && resultCode == RESULT_OK) {
            // Fill the list view with the strings the recognizer thought it
            // could have heard
            ArrayList<String> results = data.getStringArrayListExtra(RecognizerIntent.EXTRA_RESULTS);

            txtSpeechInput.setText(allWords(results));
            //txtSpeechInput.setText(results.get(0));

            //mList.setAdapter(new ArrayAdapter(this, android.R.layout.simple_list_item_1, matches));

            switch (moveArm(results)){
                case 1:
                    status.setBackgroundColor(Color.RED);
                    break;
                case 2:
                    status.setBackgroundColor(Color.GREEN);
            }

        }
    }

    public int moveArm (ArrayList<String> words){
        for (String word: retractKeys) {
            if (words.contains(word))
                return 1;
        }
        for (String word: openKeys) {
            if (words.contains(word))
                return 2;
        }
        return 0;
    }

    public String allWords (ArrayList<String> words){
        String temp = "";
        for (String word: words){
            temp+= word + ", ";
        }
        return temp;
    }
}