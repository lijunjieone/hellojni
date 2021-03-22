package com.bn.hellojni;

import android.content.Context;
import android.widget.Toast;

public class ClassMethod {


    public static String callStaticMethod(Context context, String str) {
        Toast.makeText(context,str,Toast.LENGTH_SHORT).show();
        return "java:"+str;
    }

}