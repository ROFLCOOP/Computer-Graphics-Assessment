using System.Collections;
using System.Collections.Generic;
using UnityEngine;

[RequireComponent(typeof(Animator))]
public class PlayerController : MonoBehaviour
{
    Animator anim;

    [SerializeField]
    [Range(1,50)]
    float walkSpeed = 2;

    [SerializeField]
    [Range(1, 60)]
    float runSpeed = 4;

    bool wasMoving = false;
    bool isMoving = false;

    bool isRunning = false;
    

    // Start is called before the first frame update
    void Start()
    {
        anim = GetComponent<Animator>();
    }

    // Update is called once per frame
    void Update()
    {
        if (Input.GetKeyDown(KeyCode.Escape)) Application.Quit();

        wasMoving = isMoving;
        Vector3 direction = Vector3.zero;

        if (Input.GetKey(KeyCode.W)) direction.z += 1;
        if (Input.GetKey(KeyCode.S)) direction.z -= 1;
        if (Input.GetKey(KeyCode.D)) direction.x += 1;
        if (Input.GetKey(KeyCode.A)) direction.x -= 1;

        direction.Normalize();

        if (Input.GetKeyDown(KeyCode.LeftShift) || Input.GetKeyUp(KeyCode.LeftShift)) toggleRun();
        if (Input.GetKeyDown(KeyCode.Space)) Jump();

        if (direction != Vector3.zero)
        {
            float angle = Mathf.Atan2(direction.x, direction.z) * Mathf.Rad2Deg;
            transform.rotation = Quaternion.AngleAxis(angle, Vector3.up);

            if(isRunning)
                transform.position += transform.forward * runSpeed * Time.deltaTime;
            else
                transform.position += transform.forward * walkSpeed * Time.deltaTime;

            isMoving = true;
        }
        else
        {
            isMoving = false;
        }

        if (isMoving != wasMoving)
            anim.SetBool("Moving", isMoving);
    }

    public void Jump()
    {
        if(!anim.GetCurrentAnimatorStateInfo(0).IsName("Jump"))
            anim.SetTrigger("Jump");
    }

    public void toggleRun()
    {
        isRunning = !isRunning;
        anim.SetBool("Running", isRunning);
    }
}
