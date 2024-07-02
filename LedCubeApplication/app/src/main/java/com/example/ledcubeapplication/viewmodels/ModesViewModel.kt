package com.example.ledcubeapplication.viewmodel

import androidx.lifecycle.SavedStateHandle
import androidx.lifecycle.ViewModel
import kotlinx.coroutines.flow.MutableStateFlow
import kotlinx.coroutines.flow.StateFlow

class ModesViewModel(private val state: SavedStateHandle) : ViewModel() {
    // Key for storing selections in SavedStateHandle
    companion object {
        private const val SELECTIONS_KEY = "selections"
    }

    // State to hold the checkbox selections
    private val _selections = MutableStateFlow(
        state.get<Map<String, Boolean>>(SELECTIONS_KEY) ?: initialSelections()
    )
    val selections: StateFlow<Map<String, Boolean>> get() = _selections

    // Initialize the selections with the mode options
    private fun initialSelections(): Map<String, Boolean> {
        val options = listOf(
            "FLICKER ON",
            "LAYER UP AND DOWN",
            "COLUMNS SIDEWAYS",
            //"STOMP UP AND DOWN",
            "FLICKER OFF",
            "AROUND EDGE",
            "RECTANGLE",
            "PROPELLER",
            "SPIRAL",
            "ALL LEDS"
        )
        return options.associateWith { false }
    }

    // Update the selection state
    fun updateSelection(option: String, isSelected: Boolean) {
        val updatedSelections = _selections.value.toMutableMap().apply {
            this[option] = isSelected
        }
        _selections.value = updatedSelections
        state.set(SELECTIONS_KEY, updatedSelections)
    }
}
