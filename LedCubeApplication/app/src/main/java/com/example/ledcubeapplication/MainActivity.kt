package com.example.ledcubeapplication

import android.Manifest
import android.annotation.SuppressLint
import android.bluetooth.BluetoothAdapter
import android.bluetooth.BluetoothDevice
import android.bluetooth.BluetoothManager
import android.bluetooth.BluetoothSocket
import android.content.BroadcastReceiver
import android.content.Context
import android.content.Intent
import android.content.IntentFilter
import android.content.pm.PackageManager
import android.os.Bundle
import android.widget.Toast
import androidx.activity.ComponentActivity
import androidx.activity.compose.setContent
import androidx.activity.enableEdgeToEdge
import androidx.activity.result.ActivityResultLauncher
import androidx.activity.result.contract.ActivityResultContracts
import androidx.compose.foundation.Image
import androidx.compose.foundation.background
import androidx.compose.foundation.layout.*
import androidx.compose.foundation.shape.RoundedCornerShape
import androidx.compose.material3.Button
import androidx.compose.material3.ButtonDefaults
import androidx.compose.material3.Text
import androidx.compose.runtime.*
import androidx.compose.ui.Alignment
import androidx.compose.ui.Modifier
import androidx.compose.ui.geometry.Offset
import androidx.compose.ui.graphics.Color
import androidx.compose.ui.graphics.Shadow
import androidx.compose.ui.platform.LocalContext
import androidx.compose.ui.res.painterResource
import androidx.compose.ui.text.TextStyle
import androidx.compose.ui.text.font.FontWeight
import androidx.compose.ui.unit.dp
import androidx.compose.ui.unit.sp
import androidx.core.app.ActivityCompat
import androidx.lifecycle.SavedStateViewModelFactory
import androidx.lifecycle.viewmodel.compose.viewModel
import androidx.navigation.NavHostController
import androidx.navigation.compose.NavHost
import androidx.navigation.compose.composable
import androidx.navigation.compose.rememberNavController
import com.example.ledcubeapplication.viewmodel.ModesViewModel
import java.io.IOException
import java.io.OutputStream
import java.util.UUID

class MainActivity : ComponentActivity() {
    companion object {
        val MY_UUID: UUID = UUID.fromString("00001101-0000-1000-8000-00805F9B34FB")  // Unique UUID for the Bluetooth service
        private const val REQUEST_ENABLE_BT = 1
    }

    // Object to manage Bluetooth connection
    object BluetoothConnectionManager {
        var bluetoothSocket: BluetoothSocket? = null
        var outputStream: OutputStream? = null
    }

    // Define states
    private var bluetoothAdapter: BluetoothAdapter? = null
    private val bluetoothConnection = mutableStateOf(false)
    private var bluetoothSocket: BluetoothSocket? = null
    private lateinit var bluetoothConnectionReceiver: BroadcastReceiver
    private lateinit var bluetoothStateReceiver: BroadcastReceiver
    private lateinit var requestEnableBt: ActivityResultLauncher<Intent>
    private val messageState = mutableStateOf("Welcome! Please press CONNECT")

    @SuppressLint("MissingPermission")
    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        initializeBluetooth()
        setupBluetoothReceiver()
        setupBluetoothStateReceiver()
        enableEdgeToEdge()

        // Set the content of the activity
        setContent {
            //navigation
            val navController = rememberNavController()
            val viewModel: ModesViewModel = viewModel(factory = SavedStateViewModelFactory(application, this))
            NavHost(navController = navController, startDestination = "main_screen") {
                composable("main_screen") { MainScreen(navController, this@MainActivity, messageState) }
                composable("screen_after_connection") {
                    LocalContext.current
                    ScreenAfterConnection(
                        navController
                    )
                }
                composable("modes_screen") {
                    ModesScreen(
                        viewModel = viewModel,
                        outputStream = BluetoothConnectionManager.outputStream ?: throw IllegalStateException("No Bluetooth socket available")
                    )
                }
            }
        }
    }

    // Unregister receivers when the activity is destroyed
    override fun onDestroy() {
        super.onDestroy()
        unregisterReceiver(bluetoothConnectionReceiver)
        unregisterReceiver(bluetoothStateReceiver)
    }

    override fun onResume() {
        super.onResume()
        messageState.value = "Welcome! Please press CONNECT"
    }
    // Show a toast message
    private fun sendToast(message: String) {
        Toast.makeText(this, message, Toast.LENGTH_SHORT).show()
    }

    // Initialize Bluetooth adapter
    private fun initializeBluetooth() {
        val bluetoothManager = getSystemService(Context.BLUETOOTH_SERVICE) as BluetoothManager
        bluetoothAdapter = bluetoothManager.adapter
        if (bluetoothAdapter == null) {
            messageState.value = "Bluetooth is not supported on this device"
            finish()
        } else if (!bluetoothAdapter!!.isEnabled) {
            promptEnableBluetooth()
        }
    }
    // Set up receiver for Bluetooth actions
    private fun setupBluetoothReceiver() {
        bluetoothConnectionReceiver = object : BroadcastReceiver() {
            @SuppressLint("MissingPermission")
            override fun onReceive(context: Context, intent: Intent) {
                val action: String? = intent.action
                if (BluetoothDevice.ACTION_FOUND == action) {
                    val device: BluetoothDevice = intent.getParcelableExtra(BluetoothDevice.EXTRA_DEVICE)!!
                    messageState.value = "Device found: ${device.name}"
                }
            }
        }
        val filter = IntentFilter(BluetoothDevice.ACTION_FOUND)
        registerReceiver(bluetoothConnectionReceiver, filter)
    }

    // Set up receiver for Bluetooth state changes
    private fun setupBluetoothStateReceiver() {
        bluetoothStateReceiver = object : BroadcastReceiver() {
            override fun onReceive(context: Context, intent: Intent) {
                val action: String? = intent.action
                if (BluetoothDevice.ACTION_ACL_DISCONNECTED == action) {
                    resetBluetoothConnection()  // Reset connection on disconnect
                    sendToast("Bluetooth connection lost" ) // Update message state
                }
            }
        }
        val filter = IntentFilter(BluetoothDevice.ACTION_ACL_DISCONNECTED)
        registerReceiver(bluetoothStateReceiver, filter)
    }

    // Reset Bluetooth connection
    private fun resetBluetoothConnection() {
        try {
            bluetoothSocket?.close()
        } catch (e: IOException) {
            e.printStackTrace()
        }
        BluetoothConnectionManager.bluetoothSocket = null
        BluetoothConnectionManager.outputStream = null
        bluetoothConnection.value = false
    }

    // Prompt to enable Bluetooth
    private fun promptEnableBluetooth() {
        requestEnableBt = registerForActivityResult(ActivityResultContracts.StartActivityForResult()) { result ->
            if (result.resultCode == RESULT_OK) {
                messageState.value = "Bluetooth enabled"
            } else {
                messageState.value = "Bluetooth not enabled"
            }
        }
        val enableBtIntent = Intent(BluetoothAdapter.ACTION_REQUEST_ENABLE)
        requestEnableBt.launch(enableBtIntent)
    }

    // Check if Bluetooth permissions are granted
    private fun checkBluetoothPermissions(): Boolean {
        return if (ActivityCompat.checkSelfPermission(this, Manifest.permission.BLUETOOTH_CONNECT) != PackageManager.PERMISSION_GRANTED) {
            ActivityCompat.requestPermissions(this, arrayOf(Manifest.permission.BLUETOOTH_CONNECT), REQUEST_ENABLE_BT)
            false
        } else {
            true
        }
    }
    // Check if Bluetooth is available and enabled
    private fun isBluetoothAvailable(): Boolean {
        return if (bluetoothAdapter == null || !bluetoothAdapter!!.isEnabled) {
            messageState.value = "Bluetooth is not enabled or not available"
            false
        } else {
            true
        }
    }

    // Connect to the Bluetooth device
    @SuppressLint("MissingPermission")
    fun connectToDevice(navController: NavHostController) {
        if (!checkBluetoothPermissions()) return
        if (!isBluetoothAvailable()) return
        if (bluetoothConnection.value) {
            navController.navigate("screen_after_connection")
            return
        }
        val deviceName = "HC-05"

        // Find the HC-05 device in the list of paired devices
        val device = bluetoothAdapter!!.bondedDevices.find { it.name == deviceName }
        if (device == null) {
            messageState.value = "Device not found or not paired"
            return
        }

        // Attempt to connect to the device in a background thread
        Thread {
            try {
                bluetoothSocket = device.createRfcommSocketToServiceRecord(MY_UUID)
                bluetoothSocket?.connect()  // Attempt to connect to the device

                // Connection is successful, update the UI on the main thread
                runOnUiThread {
                    if (bluetoothSocket?.isConnected == true) {
                        bluetoothConnection.value = true
                        BluetoothConnectionManager.bluetoothSocket = bluetoothSocket
                        BluetoothConnectionManager.outputStream = bluetoothSocket?.outputStream
                        sendToast("Connected to $deviceName")
                        navController.navigate("screen_after_connection")
                    } else {
                        messageState.value = "Failed to connect to $deviceName"
                    }
                }
            } catch (e: IOException) {
                // Connection failed, update the UI on the main thread
                runOnUiThread {
                    messageState.value = "Connection failed: ${e.message}"
                }
            }
        }.start()
    }


    // Disconnect from the Bluetooth device and reset connection
    fun disconnectDevice() {
        messageState.value = "Disconnected"
        resetBluetoothConnection()

    }

}

// MainScreen Composable
@Composable
fun MainScreen(navController: NavHostController, activity: MainActivity,  messageState: MutableState<String>) {
    val CustomBlue = Color(0xFF66CCFF)

    Column(
        modifier = Modifier
            .fillMaxSize()
            .background(Color.White),
        verticalArrangement = Arrangement.Center,
        horizontalAlignment = Alignment.CenterHorizontally
    ) {
        // Header box with title
        Box(
            modifier = Modifier
                .fillMaxWidth()
                .fillMaxHeight(0.15f)
                .background(CustomBlue)
                .padding(16.dp),
            contentAlignment = Alignment.Center
        ) {
            Text(
                text = "LED CUBE",
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
                .padding(16.dp),
            contentAlignment = Alignment.Center
        ) {
            Column(
                modifier = Modifier.fillMaxSize(),
                verticalArrangement = Arrangement.Center,
                horizontalAlignment = Alignment.CenterHorizontally
            ) {
                // Display message state
                Box(
                    modifier = Modifier
                        .padding(16.dp),
                    contentAlignment = Alignment.Center
                ) {
                    Text(
                        text = messageState.value,
                        fontSize = 20.sp,
                        color = Color.Black,
                        style = TextStyle(
                            fontWeight = FontWeight.Medium,
                            shadow = Shadow(
                                color = Color.Gray,
                                offset = Offset(2f, 2f),
                                blurRadius = 4f
                            )
                        ),
                        modifier = Modifier.padding(8.dp)
                    )
                }
                Spacer(modifier = Modifier.fillMaxHeight(0.02f))

                // Image of the LED cube
                Image(
                    painter = painterResource(id = R.drawable.led_cube_main),
                    contentDescription = "Led Cube image",
                    modifier = Modifier
                        .size(300.dp)
                        .padding(bottom = 16.dp)
                )
                Spacer(modifier = Modifier.fillMaxHeight(0.2f))

                // Connect button
                Button(
                    onClick = {
                        activity.connectToDevice(navController)
                    },
                    modifier = Modifier
                        .padding(10.dp)
                        .widthIn(300.dp, 350.dp)
                        .heightIn(60.dp, 80.dp),
                    shape = RoundedCornerShape(10.dp),
                    colors = ButtonDefaults.buttonColors(
                        contentColor = Color.White,
                        containerColor = CustomBlue
                    )
                ) {
                    Text(text = "CONNECT", fontSize = 32.sp)
                }

                // Disconnect button
                Button(
                    onClick = {
                        activity.disconnectDevice()
                    },
                    modifier = Modifier
                        .padding(10.dp)
                        .widthIn(300.dp, 350.dp)
                        .heightIn(60.dp, 80.dp),
                    shape = RoundedCornerShape(10.dp),
                    colors = ButtonDefaults.buttonColors(
                        contentColor = Color.White,
                        containerColor = CustomBlue
                    )
                ) {
                    Text(text = "DISCONNECT", fontSize = 32.sp)
                }
                Spacer(modifier = Modifier.fillMaxHeight(0.05f))
            }
        }
    }
}
