<!DOCTYPE html>

<head>
    <link rel="stylesheet" href="welcomeStyle.css" />
    <title>Welcome</title>
</head>

<body>
    <div class="vid-container">
        <video class="bgvid" autoplay="autoplay" muted="muted" preload="auto" loop>
            <source src="https://static.videezy.com/system/resources/previews/000/007/313/original/Plexus.mp4">
        </video>

        <div class="title">
            <?php
            if (isset($_GET['username'])) {
                echo "<h1>Welcome <span>" . $_GET['username'] . "</span>.</h1>";
            }
            ?>
        </div>

    </div>
</body>

</html>