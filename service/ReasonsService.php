<?
require_once $_SERVER['DOCUMENT_ROOT'].'/numberoneapi/models/Response.php';
require_once $_SERVER['DOCUMENT_ROOT'].'/numberoneapi/models/EnumStore.php';
require_once $_SERVER['DOCUMENT_ROOT'].'/numberoneapi/models/Response.php';
require_once $_SERVER['DOCUMENT_ROOT'].'/numberoneapi/models/entities/Reason.php';
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


// Set additional Query options
        //$query->setQueryHint('foo', 'bar');
        //$query->useResultCache('my_cache_id');

// Execute Query
        echo json_encode($query);
        /*$single = $query->getSingleResult();
        $array = $query->getArrayResult();
        $scalar = $query->getScalarResult();
        $singleScalar = $query->getSingleScalarResult();*/



        /*$query = 'select * from numberone.`one_reason`'; // where UserFromId = "'.$reasonIdFrom.'" and active = 1';
        $result = $entityManager->getRepository('Reason')->createNamedQuery($query)
            ->setMaxResults($take)
            ->setFirstResult($skip)
            ->getResult();
        $response->Data = $result;
        $response->Success = true;
        $response->Message = Constanst::DataSuccess;
        $response->Total = 10;*/
        //return $response;
    }

    function Create(Reason $createReason){
        $reason = new Reason();
        $date = new DateTime('now', new DateTimeZone('UTC'));
        $reason->setCreatedDate($date);
        $reason->setReason($createReason->getReason());
        $reason->setUserToId($createReason->getUserToId());
        $reason->setUserFromId($createReason->getUserFromId());
        $reason->setPriority($createReason->getPriority());
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