const int len_panel_page = 694;
const char *panel_page = R"EOF(
<!DOCTYPE html>
<html>
    <meta http-equiv="Cache-Control" content="no-cache, must-revalidate" />
    <meta http-equiv="Content-Type" content="text/html; charset=utf-8" />
    <meta name="viewport" content="width=device-width, initial-scale=1, user-scalable=no" />
    <title>ESP32-CAM Gimbal Panel</title>
    <style type="text/css">
        p {
            font-size: 16px;
            text-indent: 2em;
        }
    </style>
</html>
<body style="margin: 0px;">
    <div style="display: block; margin-left: auto; margin-right: auto; max-width: 640px; width: 100%;">
        <img style="width: 100%;" src="/stream" />
        <div style="width: 100%; margin-top: 8px;">
    </div>
</body>
)EOF";
