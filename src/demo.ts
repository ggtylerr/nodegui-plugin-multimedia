import {
    QMainWindow,
    QPushButton,
    QLabel,
    FlexLayout,
    QWidget,
    AlignmentFlag,
    QSlider,
    Orientation,
} from "@nodegui/nodegui";
import { QMediaPlayer, QAudioOutput } from "./index";
import path from "path";

const win = new QMainWindow();
const rootView = new QWidget();
rootView.setObjectName("root");

const player = new QMediaPlayer();
const output = new QAudioOutput();
player.setAudioOutput(output);
player.setSource(
    `file://${path.resolve(__dirname, "..", "demo.mp3")}`,
);
output.setVolume(0.5);

const button = new QPushButton();
button.setText("Play");
let playing = false;
button.addEventListener("clicked", () => {
    if (playing) {
        button.setText("Play");
        player.pause();
    } else {
        button.setText("Pause");
        player.play();
    }
    playing = !playing;
});

const text = new QLabel();
text.setText(
    "Welcome to Qt Multimedia!\nDemo song is the classic 'Black Key Etude' by Frederic Chopin. Enjoy!",
);
text.setAlignment(AlignmentFlag.AlignCenter);
const posSlider = new QSlider();
posSlider.setOrientation(Orientation.Horizontal);
const posText = new QLabel();
posText.setText("0:00/?:??");
let duration = "";
player.addEventListener("durationChanged", (dur: number) => {
    posSlider.setMaximum(dur);
    duration = `${Math.floor(dur / 1000 / 60)}:${Math.floor((dur / 1000) % 60)}`;
    posText.setText(`0:00/${duration}`);
});
posSlider.addEventListener("sliderMoved", (val: number) => {
    player.setPosition(val);
    posText.setText(
        `${Math.floor(val / 1000 / 60)}:${String(Math.floor((val / 1000) % 60)).padStart(2, "0")}/${duration}`,
    );
});
player.addEventListener("positionChanged", (pos: number) => {
    posSlider.setSliderPosition(pos);
    posText.setText(
        `${Math.floor(pos / 1000 / 60)}:${String(Math.floor((pos / 1000) % 60)).padStart(2, "0")}/${duration}`,
    );
});

const layout = new FlexLayout(rootView);
const controlsWidget = new QWidget();
controlsWidget.setObjectName("controls");
const controlsLayout = new FlexLayout(controlsWidget);
layout.addWidget(text);
layout.addWidget(controlsWidget);
controlsLayout.addWidget(button);
controlsLayout.addWidget(posSlider);
controlsLayout.addWidget(posText);

win.setCentralWidget(rootView);
win.setStyleSheet(`
  #root {
    flex: 1;
    height: '100%';
    align-items: 'center';
    justify-content: 'space-around';
  }
  #controls {
    flex-direction: row;
    gap: '16px';
  }
`);
win.setWindowTitle("NodeGUI Multimedia Demo");
win.resize(500, 300);
win.show();

// Prevent GC
(global as any).win = win;
(global as any).player = player;
(global as any).output = output;
