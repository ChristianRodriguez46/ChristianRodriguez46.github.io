package com.example.temp;

import android.annotation.SuppressLint;
import android.os.Bundle;
import android.view.MotionEvent;
import android.view.View;
import android.widget.TextView;
import android.widget.Toast;

import androidx.activity.EdgeToEdge;
import androidx.appcompat.app.AppCompatActivity;
import androidx.core.graphics.Insets;
import androidx.core.view.ViewCompat;
import androidx.core.view.WindowInsetsCompat;

public class MainActivity extends AppCompatActivity {
    CharSequence txt = "Created by: Christian Rodriguez";
    int duration = Toast.LENGTH_LONG;
    private float startY = 0;
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        EdgeToEdge.enable(this);
        setContentView(R.layout.activity_main);
        ViewCompat.setOnApplyWindowInsetsListener(findViewById(R.id.main), (v, insets) -> {
            Insets systemBars = insets.getInsets(WindowInsetsCompat.Type.systemBars());
            v.setPadding(systemBars.left, systemBars.top, systemBars.right, systemBars.bottom);
            return insets;
        });
    }
    @SuppressLint("SetTextI18n")
    public void click(View view) {
        TextView str = findViewById(R.id.textView);
        str.setText("Christian Rodriguez");
        Toast toast;
        toast = Toast.makeText(this, txt, duration);
        toast.show();
    }
    @Override
    public boolean onTouchEvent(MotionEvent event) {

        int eventaction = event.getAction();

        switch (eventaction) {
            case MotionEvent.ACTION_DOWN:
                startY = event.getY();
                break;

            case MotionEvent.ACTION_MOVE:
                float movingY = event.getY() - startY;
                int screenHeight = getWindow().getDecorView().getHeight();
                if (movingY >= (float) screenHeight /2) {
//                    Toast.makeText(this, "Swipe made. Closing app", Toast.LENGTH_SHORT).show();
                    finish();
                }
                break;
        }
        return true;
    }
}

