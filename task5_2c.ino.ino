from tkinter import Tk, Label, Scale, HORIZONTAL, Frame, Button
import tkinter.font as FONT
from gpiozero import PWMLED

# Set up PWM LEDs
red = PWMLED(6)
green = PWMLED(21)
blue = PWMLED(16)

# Create main window
window = Tk()
window.title("RGB LED Controller")
window.configure(bg='#f0f0f0')  # Light gray background

# Define fonts
title_font = FONT.Font(family='Helvetica', size=16, weight='bold')
label_font = FONT.Font(family='Arial', size=12)

# Function to update LED values
def update_color(slider, led):
    value = int(slider.get()) / 100
    led.value = value

# Create main frame to hold content
main_frame = Frame(window, padx=20, pady=20, bg='#f0f0f0')
main_frame.pack(expand=True, fill='both')

# Title label
title_label = Label(main_frame, text="RGB LED Brightness Control", font=title_font, bg='#f0f0f0', fg='#333')
title_label.pack(pady=(10, 20))

# Function to create sliders and labels
def create_slider(label_text, led, update_function, fg_color):
    slider_frame = Frame(main_frame, bg='#f0f0f0')
    slider_frame.pack(pady=10)

    label = Label(slider_frame, text=label_text, font=label_font, fg=fg_color, bg='#f0f0f0')
    label.pack(side='left', padx=10)

    slider = Scale(slider_frame, from_=0, to=100, orient=HORIZONTAL, length=250, bg='#f0f0f0', troughcolor=fg_color, highlightthickness=0)
    slider.pack(side='right')
    slider.bind("<Motion>", update_function)
    
    return slider

# Update functions for sliders
def update_red(event):
    update_color(red_slider, red)

def update_green(event):
    update_color(green_slider, green)

def update_blue(event):
    update_color(blue_slider, blue)

# Initialize sliders with colors
red_slider = create_slider("Red", red, update_red, '#ff4d4d')
green_slider = create_slider("Green", green, update_green, '#4dff4d')
blue_slider = create_slider("Blue", blue, update_blue, '#4d4dff')

# Separator line for visual grouping
def create_separator():
    separator = Frame(main_frame, height=2, bd=1, bg='#cccccc')
    separator.pack(fill='x', pady=10)

# Add separators between sliders for better grouping
create_separator()
create_separator()

# Create 'Turn Off LEDs' button
def turn_off_leds():
    red.off()
    green.off()
    blue.off()

turn_off_button = Button(main_frame, text="Turn Off LEDs", font=label_font, bg='#ff6666', fg='white', command=turn_off_leds, relief='flat', padx=10, pady=5)
turn_off_button.pack(pady=20)

# Close function
def close():
    # Turn off LEDs before closing
    turn_off_leds()
    window.destroy()

# Set close protocol
window.protocol("WM_DELETE_WINDOW", close)

# Start main loop
window.mainloop()