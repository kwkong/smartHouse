<?php

	if (isset($_POST["esp"]))
	{

		$file = fopen("text.txt", "r") or die("Unable to open file!");
		echo fgets($file);
		fclose($file);

		exit();
	}

	
	if (isset($_GET["on"]))
	{
		$file = fopen("text.txt", "w") or die("Unable to open file!");
		fwrite($file, "*");
		fclose($file);
		exit();
	}

	if (isset($_GET["off"]))
	{
		$file = fopen("text.txt", "w") or die("Unable to open file!");
		fwrite($file, "*off");
		fclose($file);
		exit();
	}

	if(isset($_GET["status"]))
	{ 

		$file = fopen("text.txt", "w") or die("Unable to open file!");
		echo 'hello';
		$status = $_GET["status"];
		fwrite($file, $status);
		fclose($file);
		exit();
	}

 ?>