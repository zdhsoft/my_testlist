plugins {
    id("com.android.application")
}
android {
    namespace = "com.zdhsoft.openbanner3"
    compileSdk = 33
    defaultConfig {
        applicationId = "com.zdhsoft.openbanner3"
        minSdk = 24
        targetSdk = 33
        versionCode = 1
        versionName = "1.0"

        testInstrumentationRunner = "androidx.test.runner.AndroidJUnitRunner"
    }

    buildTypes {
        release {
            isMinifyEnabled = false
            proguardFiles(getDefaultProguardFile("proguard-android-optimize.txt"), "proguard-rules.pro")
        }
    }
    compileOptions {
        sourceCompatibility = JavaVersion.VERSION_1_8
        targetCompatibility = JavaVersion.VERSION_1_8
    }
}

dependencies {

    implementation("androidx.appcompat:appcompat:1.6.1")
    implementation("com.google.android.material:material:1.9.0")
    implementation("androidx.constraintlayout:constraintlayout:2.1.4")
    implementation("io.github.youth5201314:banner:2.2.2")
    implementation("com.github.bumptech.glide:glide:4.16.0")
    // implementation("com.jakewharton:butterknife:10.2.3")
    // annotationProcessor("com.jakewharton:butterknife-compiler:10.2.3")
    implementation("androidx.swiperefreshlayout:swiperefreshlayout:1.1.0")
    implementation("com.github.CarGuo.GSYVideoPlayer:GSYVideoPlayer:v8.4.0-release-jitpack")
    testImplementation("junit:junit:4.13.2")
    androidTestImplementation("androidx.test.ext:junit:1.1.5")
    androidTestImplementation("androidx.test.espresso:espresso-core:3.5.1")
}