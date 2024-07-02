package com.example.ledcubeapplication

import androidx.compose.foundation.background
import androidx.compose.foundation.layout.Arrangement
import androidx.compose.foundation.layout.Box
import androidx.compose.foundation.layout.Column
import androidx.compose.foundation.layout.PaddingValues
import androidx.compose.foundation.layout.Row
import androidx.compose.foundation.layout.Spacer
import androidx.compose.foundation.layout.fillMaxHeight
import androidx.compose.foundation.layout.fillMaxSize
import androidx.compose.foundation.layout.fillMaxWidth
import androidx.compose.foundation.layout.padding
import androidx.compose.foundation.lazy.LazyColumn
import androidx.compose.foundation.lazy.items
import androidx.compose.foundation.shape.RoundedCornerShape
import androidx.compose.material3.Checkbox
import androidx.compose.material3.Text
import androidx.compose.runtime.Composable
import androidx.compose.runtime.collectAsState
import androidx.compose.ui.Alignment
import androidx.compose.ui.Modifier
import androidx.compose.ui.geometry.Offset
import androidx.compose.ui.graphics.Color
import androidx.compose.ui.graphics.Shadow
import androidx.compose.ui.text.TextStyle
import androidx.compose.ui.text.font.FontWeight
import androidx.compose.ui.unit.dp
import androidx.compose.ui.unit.sp
import com.example.ledcubeapplication.viewmodel.ModesViewModel
import java.io.IOException
import java.io.OutputStream

@Composable
fun ModesScreen(
    viewModel: ModesViewModel,
    outputStream: OutputStream
) {
    val selections = viewModel.selections.collectAsState().value

    // Define mode commands within the composable
    val modeCommands = mapOf(
        "FLICKER ON" to "command_flicker_on",
        "LAYER UP AND DOWN" to "command_layer_up_down",
        "COLUMNS SIDEWAYS" to "command_columns_sideways",
        //  "STOMP UP AND DOWN" to "command_stomp_up_down",
        "FLICKER OFF" to "command_flicker_off",
        "AROUND EDGE" to "command_around_edge",
        "RECTANGLE" to "command_rectangle",
        "PROPELLER" to "command_propeller",
        "SPIRAL" to "command_spiral",
        "ALL LEDS" to "command_all_leds"
    )

    Column(
        modifier = Modifier.fillMaxSize(),
        verticalArrangement = Arrangement.Center,
        horizontalAlignment = Alignment.CenterHorizontally
    ) {
        // Header box with title
        Box(
            modifier = Modifier
                .fillMaxWidth()
                .fillMaxHeight(0.15f)
                .background(Color(0xFF66CCFF))
                .padding(16.dp),
            contentAlignment = Alignment.Center
        ) {
            Text(
                text = "SELECT MODE",
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

        // Main content box
        Box(
            modifier = Modifier
                .fillMaxSize()
                .background(Color.White)
        ) {
            // Display the list of modes with checkboxes
            ModesList(
                selections = selections,
                onSelectionChange = { option, isSelected ->
                    viewModel.updateSelection(option, isSelected)
                    val command = if (isSelected) {
                        modeCommands[option]?.plus("_on")
                    } else {
                        modeCommands[option]?.plus("_off")
                    }
                    command?.let { sendCommandToHC05(outputStream, it) }
                }
            )
        }
        Spacer(modifier = Modifier.fillMaxHeight(0.2f))
    }
}

@Composable
fun ModesList(
    selections: Map<String, Boolean>,
    onSelectionChange: (String, Boolean) -> Unit
) {
    LazyColumn(
        modifier = Modifier.padding(16.dp),
        contentPadding = PaddingValues(bottom = 48.dp)
    ) {
        items(items = selections.keys.toList()) { option ->
            SelectableMode(
                option = option,
                isChecked = selections[option] ?: false,
                onSelectionChange = onSelectionChange
            )
        }
    }
}

@Composable
fun SelectableMode(
    option: String,
    isChecked: Boolean,
    onSelectionChange: (String, Boolean) -> Unit
) {
    Row(
        modifier = Modifier
            .fillMaxWidth()
            .padding(16.dp)
            .background(Color(0xFFECECEC), shape = RoundedCornerShape(8.dp))
            .padding(16.dp),
        verticalAlignment = Alignment.CenterVertically
    ) {
        // Checkbox to select/deselect the mode
        Checkbox(
            checked = isChecked,
            onCheckedChange = { isSelected ->
                onSelectionChange(option, isSelected)
            },
            modifier = Modifier.padding(end = 8.dp)
        )
        // Display the mode option text
        Text(
            text = option,
            style = TextStyle(fontSize = 20.sp, fontWeight = FontWeight.Medium),
            modifier = Modifier.padding(start = 8.dp)
        )
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