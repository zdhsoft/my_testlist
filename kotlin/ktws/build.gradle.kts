plugins {
    kotlin("jvm") version "1.9.22"
    application
}

group = "com.zdhsoft"
version = "1.0-SNAPSHOT"

repositories {
    mavenCentral()
}
dependencies {
    testImplementation(kotlin("test"))
    implementation("com.squareup.okhttp3:okhttp:4.9.0")

}

tasks.test {
    useJUnitPlatform()
}

tasks.named<JavaExec>("run") {
    standardInput = System.`in`
}

kotlin {
    jvmToolchain(8)
}

application {
    mainClass.set("MainKt")
}