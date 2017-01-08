<?php
require_once('header.php');
$action = $_['action'];
if(isset($_SERVER['argv']))list($file,$action,$sender,$value,$positive) = $_SERVER['argv'];



switch($action){

case 'ADD_ENGINE':
	$db = (file_exists(PATH_BDD)?Functions::unstore():array());
    $fichier = basename($_FILES['picture']['name']);
    move_uploaded_file($_FILES['picture']['tmp_name'], PICTURE_FOLDER .'/'. $fichier);
	$newEngine['picture'] = PICTURE_FOLDER .'/'.$fichier;
	$newEngine['name'] = $_['name'];
	$newEngine['code'] = $_['code'];
	$newEngine['state'] = ($_['idType']==0?'off':'-');
	$newEngine['description'] = $_['description'];
	$newEngine['place'] = $_['idPlace'];
	$newEngine['type'] = $_['idType'];
	$db['keys']['engines']=(isset($db['keys']['engines'])?$db['keys']['engines']+1:1);
	$db['engines']['id-'.$db['keys']['engines']] =  $newEngine;
	Functions::store($db);
	header('location: settings.php');
break;



case 'LOGIN':
	if($_['email']==EMAIL && $_['password']==PASSWORD){
		$_SESSION['myUser'] = serialize(array('login'=>EMAIL));
	}else{
		exit('Bad code');
	}
	header('location: index.php');
break;

case 'DISCONNECT':
	$_SESSION = array();
	session_unset();
	session_destroy();
	header('location: index.php');
break;

case 'ADD_PLACE':
	$db = (file_exists(PATH_BDD)?Functions::unstore():array());
	$newPlace['name'] = $_['place'];
	$db['keys']['places']=(isset($db['keys']['places'])?$db['keys']['places']+1:1);
	$db['places']['id-'.$db['keys']['places']] =  $newPlace;
	Functions::store($db);
	header('location: settings.php');
break;

case 'DELETE_ENGINE':
	$db = (file_exists(PATH_BDD)?Functions::unstore():array());
	unset($db['engines'][$_['engine']]);
	Functions::store($db);
	header('location: settings.php');
break;

case 'DELETE_PLACE':
	$db = (file_exists(PATH_BDD)?Functions::unstore():array());
	unset($db['places'][$_['place']]);
	Functions::store($db);
	header('location: settings.php');
break;

case 'GET_ENGINE_STATE':
	$db = (file_exists(PATH_BDD)?Functions::unstore():array());
	$engines = $db['engines'];
	
	$temperature = $engines[$_['engine']]['state'];
	if(isset($_['provider']) && $_['provider']=="yuri"){
		echo 'Il fait '.$temperature.' degrais'.($temperature<20?',c\'est froid, prend ta petite laine!':',c\'est chaud, il faut se mettre tout nue et danser le tcha tcha tcha!');
	}else{
		echo $temperature;
	}
	
break;

case 'UPDATE_ENGINE_STATE':
	$db = (file_exists(PATH_BDD)?Functions::unstore():array());
	$engines = $db['engines'];
	foreach($engines as $id=>$engine){
		if ($engine['code']==$sender){
			$engine['state'] = ($positive?'+':'-').$value;
			$db['engines'][$id] =  $engine;
			Functions::store($db);
		}
	}
break;


case 'CHANGE_STATE':
	$db = (file_exists(PATH_BDD)?Functions::unstore():array());
	
	if($_GET['code']=='-1'){
		foreach($db['engines'] as $id=>$engine){
			system(' ./radioEmission '.PIN.' '.SENDER.' '.$engine['code'].' '.$_GET['state']);
		}
	}else{
		system(' ./radioEmission '.PIN.' '.SENDER.' '.$_GET['code'].' '.$_GET['state']);
	}
	$db[$_GET['code']] = $_GET['state'];
	$engine = $db['engines'][$_['engine']];
	$engine['state'] = $_['state'];
	$db['engines'][$_['engine']] =  $engine;

	Functions::store($db);
	
	if(isset($_['provider']) && $_['provider']=="yuri"){
		echo 'A vos ordres';
	}else{
		header('location: index.php');
	}
break;



	case 'GET_YURI_XML':
		$db = (file_exists(PATH_BDD)?Functions::unstore():array());
		$hccPath = substr($_SERVER['HTTP_REFERER'],0,strrpos($_SERVER['HTTP_REFERER'], '/')).'/action.php';

		$template = '<grammar version="1.0" xml:lang="fr-FR" mode="voice" root="ruleEedomus" xmlns="http://www.w3.org/2001/06/grammar" tag-format="semantics/1.0">
						  <rule id="ruleEedomus" scope="public">
						    <example>Yuri allume le salon</example>
						    <tag>out.action=new Object(); </tag>
						    <item>Yuri</item>
						    <one-of>
						      <item>allume<tag>out.action.state="on"</tag></item>
						      <item>eteint<tag>out.action.state="off"</tag></item>
						    </one-of>

						    <one-of>';

						    foreach($db['engines'] as $id=>$engine){
						    $template .= '<item>'.$engine['name'].'
						        <tag>out.action.engine=\''.$id.'\'</tag>
								<tag>out.action.code=\''.$engine['code'].'\'</tag>
						      </item>';
							}
						   


						  $template .= '

						  	<item>tout
						        <tag>out.action.engine=\'id-all\'</tag>
								<tag>out.action.code=\'-1\'</tag>
						      </item>

						   </one-of>
						    <tag>out.action.action=\'CHANGE_STATE\'</tag>
							 <tag>out.action.provider=\'yuri\'</tag>
							  <tag>out.action._attributes.threashold="0.80";</tag>
						    <tag>out.action._attributes.uri="'.$hccPath.'";</tag>
						  </rule>
						</grammar>';

						header('Content-Description: File Transfer');
			    		header('Content-Type: application/octet-stream');
			    		header('Content-Disposition: attachment; filename=hcc_yuri_xml.xml');
			    		header('Content-Transfer-Encoding: binary');
			    		header('Expires: 0');
			   	 		header('Cache-Control: must-revalidate');
			    		header('Pragma: public');
			    		header('Content-Length: ' . strlen($template));
			    		ob_clean();
			    		flush();
						echo $template;
				
	break;
	default:
		echo 'Aucune action correcte n\'est spécifiée';
	break;

}





?>