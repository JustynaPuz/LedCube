package com.example.ledcubeapplication

import android.widget.Toast
import androidx.compose.foundation.background
import androidx.compose.foundation.layout.Arrangement
import androidx.compose.foundation.layout.Box
import androidx.compose.foundation.layout.Column
import androidx.compose.foundation.layout.Spacer
import androidx.compose.foundation.layout.fillMaxHeight
import androidx.compose.foundation.layout.fillMaxSize
import androidx.compose.foundation.layout.fillMaxWidth
import androidx.compose.foundation.layout.heightIn
import androidx.compose.foundation.layout.padding
import androidx.compose.foundation.layout.widthIn
import androidx.compose.foundation.shape.RoundedCornerShape
import androidx.compose.material3.Button
import androidx.compose.material3.ButtonDefaults
import androidx.compose.material3.Text
import androidx.compose.runtime.Composable
import androidx.compose.runtime.remember
import androidx.compose.ui.Alignment
import androidx.compose.ui.Modifier
import androidx.compose.ui.geometry.Offset
import androidx.compose.ui.graphics.Color
import androidx.compose.ui.graphics.Shadow
import androidx.compose.ui.platform.LocalContext
import androidx.compose.ui.text.TextStyle
import androidx.compose.ui.text.font.FontWeight
import androidx.compose.ui.unit.dp
import androidx.compose.ui.unit.sp
import androidx.navigation.NavHostController
import java.io.IOException
import java.io.OutputStream

@Composable
fun ScreenAfterConnection(navController: NavHostController) {
    val context = LocalContext.current
    val CustomBlue = Color(0xFF66CCFF)
    val bluetoothSocket = remember { MainActivity.BluetoothConnectionManager.bluetoothSocket }
    val outputStream = remember { MainActivity.BluetoothConnectionManager.outputStream }

    if (bluetoothSocket == null || outputStream == null) {
        Toast.makeText(context, "No Bluetooth connection available", Toast.LENGTH_SHORT).show()
        navController.popBackStack()
        return
    }

    Column(
        modifier = Modifier.fillMaxSize(),
        verticalArrangement = Arrangement.Center,
        horizontalAlignment = Alignment.CenterHorizontally
    ) {
        Box(
            modifier = Modifier
                .fillMaxWidth()
                .fillMaxHeight(0.15f)
                .background(CustomBlue)
                .padding(16.dp),
            contentAlignment = Alignment.Center
        ) {
            Text(
                text = "CUSTOMIZE",
                style = TextStyle(
                    color = Color.White,
                    fontSize = 55.sp,
                    fontWeight = FontWeight.Bold,
                    shadow = Shadow(
                        color = Color.Gray,
                        offset = Offset(4f, 4f),
                        blurRadius = 8f
                    )
                )
            )
        }
        Box(
            modifier = Modifier
                .fillMaxSize()
                .background(Color.White)
        ) {
            Column(
                modifier = Modifier.fillMaxSize(),
                verticalArrangement = Arrangement.Center,
                horizontalAlignment = Alignment.CenterHorizontally
            ) {
                Button(
                    onClick = {
                        sendCommandToHC05(outputStream, "all_leds_on")
                        sendCommandToHC05(outputStream, "on")
                    },
                    modifier = Modifier
                        .weight(1f)
                        .padding(30.dp)
                        .widthIn(300.dp, 350.dp)
                        .heightIn(50.dp, 150.dp),
                    shape = RoundedCornerShape(5.dp),
                    colors = ButtonDefaults.buttonColors(
                        contentColor = Color.White,
                        containerColor = CustomBlue
                    )
                ) {
                    Text(text = "TURN ON", fontSize = 40.sp)
                }

                Button(
                    onClick = {
                        sendCommandToHC05(outputStream, "all_leds_off")
                        sendCommandToHC05(outputStream, "off")
                    },
                    modifier = Modifier
                        .weight(1f)
                        .padding(30.dp)
                        .widthIn(300.dp, 350.dp)
                        .heightIn(50.dp, 150.dp),
                    shape = RoundedCornerShape(5.dp),
                    colors = ButtonDefaults.buttonColors(
                        contentColor = Color.White,
                        containerColor = CustomBlue
                    )
                ) {
                    Text(text = "TURN OFF", fontSize = 40.sp)
                }

                Button(
                    onClick = {
                        navController.navigate("modes_screen")
                    },
                    modifier = Modifier
                        .weight(1f)
                        .padding(30.dp)
                        .widthIn(300.dp, 350.dp)
                        .heightIn(50.dp, 150.dp),
                    shape = RoundedCornerShape(5.dp),
                    colors = ButtonDefaults.buttonColors(
                        contentColor = Color.White,
                        containerColor = CustomBlue
                    )
                ) {
                    Text(text = "MODES", fontSize = 40.sp)
                }
                Spacer(modifier = Modifier.fillMaxHeight(0.2f))
            }
        }
    }
}

private fun sendCommandToHC05(outputStream: OutputStream, command: String) {
    val commandWithCarriageReturn = "$command\r"
    try {
        outputStream.write(commandWithCarriageReturn.toByteArray())
        outputStream.flush()
    } catch (e: IOException) {
        e.printStackTrace()
    }
}
