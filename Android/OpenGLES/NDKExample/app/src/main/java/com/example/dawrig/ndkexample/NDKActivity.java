package com.example.dawrig.ndkexample;

import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.util.Log;
import android.view.Menu;
import android.view.MenuItem;
import android.view.View;
import android.widget.ArrayAdapter;
import android.widget.Button;
import android.widget.EditText;
import android.widget.Spinner;
import android.widget.Toast;

import java.util.regex.Pattern;

public class NDKActivity extends AppCompatActivity {

    private Store store = new Store();
    private EditText keyEdit, valueEdit;
    private Spinner typeSpinner;
    private Button getButton, setButton;
    private Pattern keyPattern;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_ndk);

        keyPattern = Pattern.compile("\\p{Alnum}+");
        keyEdit = (EditText)findViewById(R.id.key_edit);
        valueEdit = (EditText)findViewById(R.id.value_edit);
        typeSpinner = (Spinner)findViewById(R.id.type_spinner);

        ArrayAdapter<StoreType> adapter = new ArrayAdapter<StoreType>(this,android.R.layout.simple_spinner_item,StoreType.values());
        adapter.setDropDownViewResource(android.R.layout.simple_spinner_dropdown_item);
        typeSpinner.setAdapter(adapter);

        getButton = (Button)findViewById(R.id.get_button);
        getButton.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                onGetValue();
            }
        });
        setButton = (Button)findViewById(R.id.set_button);

        setButton.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                onSetValue();
            }
        });
    }

    private void onGetValue() {
        String key = keyEdit.getText().toString();
        StoreType type = (StoreType)typeSpinner.getSelectedItem();
        if(!keyPattern.matcher(key).matches()){
            displayMessage("Incorrect Key");
            return;
        }

        switch (type) {
            case Integer:
                valueEdit.setText(Integer.toString(store.getInteger(key)));
                break;
            case String:
                valueEdit.setText(store.getString(key));
                break;
        }
    }

    private void onSetValue() {
        String key = keyEdit.getText().toString();
        String value = valueEdit.getText().toString();
        StoreType type = (StoreType)typeSpinner.getSelectedItem();
        if(!keyPattern.matcher(key).matches()){
            displayMessage("Incorrect Key");
            return;
        }
        try{
            switch (type) {
                case Integer:
                    store.setInteger(key,Integer.parseInt(value));
                    break;
                case String:
                    store.setString(key,value);
                    break;
            }
        }catch (Exception e) {

        }
    }

    private void displayMessage(String message) {
        Toast.makeText(this.getApplicationContext(),message,Toast.LENGTH_SHORT).show();
    }
}
