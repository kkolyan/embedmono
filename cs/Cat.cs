using System;
using System.Runtime.InteropServices;

public class Cat {
    [DllImport ("__Internal", EntryPoint="SayMyaw")]
    extern static void SayMyaw();

    public static void SaySomething() {
        SayMyaw();
    }
}