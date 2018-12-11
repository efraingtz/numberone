<?
require_once $_SERVER['DOCUMENT_ROOT'].'/numberoneapi/models/Response.php';
require_once $_SERVER['DOCUMENT_ROOT'].'/numberoneapi/models/EnumStore.php';
require_once $_SERVER['DOCUMENT_ROOT'].'/numberoneapi/models/Response.php';
require_once $_SERVER['DOCUMENT_ROOT'].'/numberoneapi/models/entities/Reason.php';
require_once $_SERVER['DOCUMENT_ROOT'].'/numberoneapi/models/entities/User.php';
require_once $_SERVER['DOCUMENT_ROOT']."/numberoneapi/bootstrap.php";

class ReasonsService
{
    function GetDashboard()
    {
        $take = $_GET["take"];
        $skip = $_GET["skip"];
        $usertoid = $_GET["usertoid"];
        $response = new PagedResult();
        global $entityManager;

        $repo   = $entityManager->getRepository('Reason');
        $query = $repo->findBy(array('UserToId' => $usertoid, 'Active' => '1'), array('Priority' => 'DESC', 'ReasonId' => 'DESC'), $take, $skip);
        $count = $repo->count(array('UserToId' => $usertoid, 'Active' => '1'));

        foreach($query as $k => $reason)
        {
            $repo = $entityManager->getRepository('User');
            $user = $repo->find($reason->UserFromId);
            $reason->UserFromName = $user->UserName;
        }

        $response->Data = $query;
        $response->Success = true;
        $response->Message = Constanst::DataSuccess;
        $response->Total = $count;
        return $response;
    }

    function Create(Reason $createReason){
        $reason = new Reason();
        $date = new DateTime('now', new DateTimeZone('UTC'));
        $reason->setCreatedDate($date);
        $reason->setReason($createReason->getReason());
        $reason->setUserToId($createReason->getUserToId());
        $reason->setUserFromId($createReason->getUserFromId());
        $reason->setPriority($createReason->getPriority());
        $reason->setNumber($createReason->getNumber());
        global $entityManager;
        $entityManager->persist($reason);
        $entityManager->flush();
        $response = new SingleResult();
        $response->Data = $reason->ReasonId;
        $response->Success = true;
        $response->Message = Constanst::DataCreated;
        $response->Total = 10;
        return $response;
    }
}

?>