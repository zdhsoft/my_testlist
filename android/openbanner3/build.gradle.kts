// Top-level build file where you can add configuration options common to all sub-projects/modules.
plugins {
    id("com.android.application") version "8.1.1" apply false
}

apply(plugin = "com.jakewharton.butterknife")
// apply(plugin = "com.android.library")
buildscript {
    repositories {
        gradlePluginPortal()
    }
    dependencies {
        classpath("com.jakewharton:butterknife-gradle-plugin:10.2.3")
    }
}
