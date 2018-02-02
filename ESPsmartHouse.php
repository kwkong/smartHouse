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
		$file = fopen("text.txt", "r") or die("Unable to open file!");
		$status = fgets($file);
		$face = substr($status,4,1);
		fclose($file);

		$file1 = fopen("text.txt", "w") or die("Unable to open file!");
		$status = $_GET["status"];
		fwrite($file1, $status . $face);
		fclose($file1);
		exit();
	}

        if(isset($_GET["face"]))
	{
             $file = fopen("text.txt", "r") or die("Unable to open file!");
             $status = fgets($file);
             fclose($file);
             $file1 = fopen("text.txt", "w") or die("Unable to open file!");
             $status = substr($status,0,3);
             fwrite($file1, $status . $_GET["face"]);
             fclose($file1);
             exit();

	}

 ?>
